/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miso_parser.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jemustaj <jemustaj@student.42Porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/12 22:48:03 by jemustaj          #+#    #+#             */
/*   Updated: 2026/02/24 20:18:36 by jemustaj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	miso_parser(t_shell *miso)
{
	t_token	*temp;

	temp = miso->list.head;
	while (temp)
	{
		search_cmd(miso, temp);
		while (temp && temp->type != PIPE)
		{
			if (ft_strchr("<|>", temp->str))
				if (parse_redirections(temp))
					return (1);
			temp = temp->next;
		}
		if (temp->type == PIPE)
			if (parse_pipe(temp))
				return (1);
		miso->list.cmd_found = 0;
		temp = temp->next;
	}
	return (0);
}

void	search_cmd(t_shell *miso, t_token *node)
{
	if (node->type == ARG)
	{
		set_commandtype(miso, node);
		miso->list.cmd_found = 1;
	}
}

int	parse_redirections(t_shell *miso, t_token *node)
{
	if (ft_strchr("<|>", miso->list.last_node->type))
	{
		miso->list.syntax_err = 1;
		racc_print(2, BLOD"PROMPT"MINT" Syntax error near redirection operator\n");
		return (1);
	}
	else if (node->next->type == ARG && node->next->ne)
	{
		if (miso->list.cmd_found == 0)
		{
			set_commandtype(miso, node);
			return (0);
		}
	}
}

int	parse_pipe(t_shell *miso, t_token *node)
{
	if (miso->list.cmd_found == 0)
	{
		miso->list.syntax_err = 1;
		racc_print(2, BLOD"PROMPT"MINT" Syntax error near PIPE\n");
		return (1);
	}
	if (miso->list.head->type == PIPE || miso->list.last_node->type == PIPE)
	{
		miso->list.syntax_err = 1;
		racc_print(2, BLOD"PROMPT"MINT" Syntax error near PIPE\n");
		return (1);
	}
	else if (node->type == PIPE && node->next->type == PIPE)
	{
		miso->list.syntax_err = 1;
		racc_print(2, BLOD"PROMPT"MINT" Syntax error near PIPE\n");
		return (1);
	}
	return (0);
}
