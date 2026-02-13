/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miso_tokenization.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jemustaj <jemustaj@student.42Porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/29 22:47:33 by jemustaj          #+#    #+#             */
/*   Updated: 2026/02/13 15:03:15 by jemustaj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

void	miso_token_list(t_shell *miso, char *line)
{
	t_line	*list;
	int		i;

	list = malloc(sizeof(t_line));
	if (!list)
		return ;
	i = 0;
	while (line[i])
	{
		while (line[i] && is_whitespace(line[i]))
			i++;
		if (ft_strchr("<|>", line[i]) != NULL)
			add_operator(miso, &line[i], &i);
		else if (line[i] == '\'')
			add_argument(miso, &line[++i], &i, is_squote);
		else if (line[i] == '"')
			add_argument(miso, &line[++i], &i, is_dquote);
		else
			add_argument(miso, &line[i], &i, is_whitespace);
	}
}

void	add_operator(t_shell *miso, char *line, int *pi)
{
	if (line[*pi] == '|')
	{
		add_to_list(miso, "|", PIPE);
		*pi += 1;
	}
	else if (line[*pi] == '<' || line[*pi] == '>')
		add_redirection(miso, &line[*pi], pi);
}

void	add_redirection(t_shell *miso, char *line, int *pi)
{
	if (line[*pi] == '<')
	{
		if (line[*pi++] == '<')
		{
			add_to_list(miso, "<<", HEREDOC);
			*pi += 1;
		}
		else
			add_to_list(miso, "<", RD_IN);
	}
	else if (line[*pi] == '<')
	{
		if (line[*pi++] == '<')
		{
			add_to_list(miso, "<<", HEREDOC);
			*pi += 1;
		}
		else
			add_to_list(miso, "<", RD_IN);
	}
	*pi += 1;
}

void	add_argument(t_shell *miso, char *line, int *pi, int (*f)(char))
{
	char	*temp;
	int		i;

	temp = malloc(sizeof(char) * ft_strlen(line) + 1);
	if (!temp)
		return ;
	i = 0;
	while (line[i])
	{
		if ((*f)(line[i]))
		{
			i++;
			break ;
		}
		else if (line[i] == '$' && line[0] == '\'')
			miso->node->expand = 1;
		temp[i] = line[i];
		i++;
	}
	temp[i] = '\0';
	*pi += i;
//	if (!(*f)(line[*pi]))
//		print syntax error
	add_to_list(miso, temp, ARG);
}

void	add_to_list(t_shell *miso, char *str, t_token_type type)
{
	t_token	*new_node;

	new_node = malloc(sizeof(t_token));
	if (!new_node)
		return ;
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
