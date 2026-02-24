/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miso_tokenization.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jemustaj <jemustaj@student.42Porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/29 22:47:33 by jemustaj          #+#    #+#             */
/*   Updated: 2026/02/24 10:46:10 by jemustaj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/parsing.h"

void	miso_tokenization(t_shell *miso, char *line)
{
	int		i;

	i = 0;
	while (line[i] && !miso->list.syntax_err)
	{
		while (line[i] && is_whitespace(line[i]))
			i++;
		if (ft_strchr("<|>", line[i]) != NULL)
			add_operator(miso, &line[i], &i);
		else if (line[i] == '\'')
			add_quotes(miso, &line[++i], &i, is_squote);
		else if (line[i] == '"')
			add_quotes(miso, &line[++i], &i, is_dquote);
		else if (line[i])
			add_argument(miso, &line[i], &i, is_whitespace);
	}
}

void	add_operator(t_shell *miso, char *str, int *pi)
{
	int	i;

	i = 0;
	if (str[i] == '|')
	{
		add_to_list(miso, "|", PIPE);
		*pi += 1;
	}
	else
		add_redirection(miso, str, pi);
}

void	add_redirection(t_shell *miso, char *str, int *pi)
{
	int	i;

	i = 0;
	if (str[i] == '<')
	{
		if (str[i + 1] == '<')
		{
			add_to_list(miso, "<<", HEREDOC);
			*pi += 1;
		}
		else
			add_to_list(miso, "<", RD_IN);
	}
	else if (str[i] == '>')
	{
		if (str[i + 1] == '>')
		{
			add_to_list(miso, ">>", APPEND);
			*pi += 1;
		}
		else
			add_to_list(miso, ">", RD_OUT);
	}
	*pi += 1;
}

void	add_argument(t_shell *miso, char *str, int *pi, int (*f)(char))
{
	int		i;
	int		len;
	char	*temp;

	if (miso->list.syntax_err)
		return ;
	miso->node->expand = 0;
	len = 0;
	while (str[len] && !is_whitespace(str[len]) && !ft_strchr("<|>'\"", str[len]))
	{
		if (str[len] == '$' && miso->node->expand == 0)
			miso->node->expand = 1;
		len++;
	}
	temp = create_token_str(str, len);
	add_to_list(miso, temp, ARG);
}

void	add_to_list(t_shell *miso, char *str, t_token_type type)
{
	t_token	*new_node;

	new_node = malloc(sizeof(t_token));
	if (!new_node)
	{
		perror(BLOD"PROMPT"MINT");
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
