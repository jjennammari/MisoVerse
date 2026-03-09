/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miso_tokenize.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jemustaj <jemustaj@student.42Porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/29 22:47:33 by jemustaj          #+#    #+#             */
/*   Updated: 2026/03/08 22:22:13 by lde-san-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/miso.h"

int	miso_tokenize(t_shell *miso, char *line)
{
	int		i;

	i = 0;
	while (line[i])
	{
		while (line[i] && miso_is_whitespace(line[i]))
			i++;
		if (ft_strchr("<|>", line[i]) != NULL)
			miso_add_operator(miso, &line[i], &i);
		else if (line[i] == '\'')
		{
			if (miso_add_quotes(miso, &line[++i], &i, miso_is_squote))
				return (1);
		}
		else if (line[i] == '"')
		{
			if (miso_add_quotes(miso, &line[++i], &i, miso_is_dquote))
				return (1);
		}
		else if (line[i])
			miso_add_argument(miso, &line[i]);
	}
	return (0);
}

void	miso_add_operator(t_shell *miso, char *str, int *pi)
{
	int	i;

	miso->node->is_quotet = 0;
	i = 0;
	if (str[i] == '|')
	{
		miso_add_to_list(miso, "|", PIPE);
		*pi += 1;
	}
	else
		miso_add_redirection(miso, str, pi);
}

void	miso_add_redirection(t_shell *miso, char *str, int *pi)
{
	int	i;

	i = 0;
	if (str[i] == '<')
	{
		if (str[i + 1] == '<')
		{
			miso_add_to_list(miso, "<<", HEREDOC);
			miso->list.hd_count += 1;
			*pi += 1;
		}
		else
			miso_add_to_list(miso, "<", RD_IN);
	}
	else if (str[i] == '>')
	{
		if (str[i + 1] == '>')
		{
			miso_add_to_list(miso, ">>", APPEND);
			*pi += 1;
		}
		else
			miso_add_to_list(miso, ">", RD_OUT);
	}
	*pi += 1;
}

void	miso_add_argument(t_shell *miso, char *str)
{
	int		len;
	char	*temp;

	miso->node->expand = 0;
	miso->node->is_quotet = 0;
	len = 0;
	while (str[len] && !miso_is_whitespace(str[len]) && !ft_strchr("<|>'\"", str[len]))
	{
		if (str[len] == '$' && miso->node->expand == 0)
			miso->node->expand = 1;
		len++;
	}
	temp = miso_create_token_str(str, len);
	miso_add_to_list(miso, temp, ARG);
}

void	miso_add_to_list(t_shell *miso, char *str, t_token_type type)
{
	t_token	*new_node;

	new_node = malloc(sizeof(t_token));
	if (!new_node)
	{
		perror(BLOD"PROMPT"MINT);
		// function that mapache makes to free and exit
	}
	new_node->str = str;
	new_node->type = type;
	new_node->next = NULL;
	if (miso->list.last_node)
	{
		miso->list.last_node->next = new_node;
		miso->list.last_node = new_node;
	}
	if (!miso->list.last_node)
		miso->list.last_node = new_node;
	if (miso->list.head == NULL)
		miso->list.head = new_node;
}
