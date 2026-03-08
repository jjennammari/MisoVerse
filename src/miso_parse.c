/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miso_parser.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jemustaj <jemustaj@student.42Porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/12 22:48:03 by jemustaj          #+#    #+#             */
/*   Updated: 2026/03/04 19:23:12 by jemustaj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/miso.h"

int	miso_parse(t_shell *miso)
{
	t_token	*temp;

	temp = miso->list.head;
	while (temp)
	{
		miso_search_cmd(miso, temp);
		while (temp && temp->type != PIPE)
		{
			if (miso_is_redirection(temp->type))
			{
				if (miso_parse_redirections(miso, temp))
					return (1);
			}
			else if (temp->expand == 1)
				miso_expand(miso, temp->str);
			temp = temp->next;
		}
		if (temp->type == PIPE)
			if (miso_parse_pipe(miso, temp))
				return (1);
		miso->list.cmd_found = 0;
		if (temp)
			temp = temp->next;
	}
	return (0);
}

int	miso_parse_redirections(t_shell *miso, t_token *node)
{
	if (miso_is_redirection(miso->list.last_node->type))
	{
		racc_print(2, BLOD"PROMPT"MINT" Syntax error near redirection operator\n");
		return (1);
	}
	else if (node->next->type != ARG)
	{
		racc_print(2, BLOD"PROMPT"MINT" Syntax error near redirection operator\n");
		return (1);
	}
	if (node->type == HEREDOC)
		node->next->expand = 0;
	if (node->next->type == ARG && node->next->next->type == ARG)
	{
		if (miso->list.cmd_found == 0)
		{
			miso_set_commandtype(miso, node->next->next);
			miso->list.cmd_found = 1;
		}
		return (0);
	}
	return (0);
}

int	miso_parse_pipe(t_shell *miso, t_token *node)
{
	if (miso->list.cmd_found == 0)
	{
		racc_print(2, BLOD"PROMPT"MINT" Syntax error near pipe\n");
		return (1);
	}
	else if (miso->list.head->type == PIPE || miso->list.last_node->type == PIPE)
	{
		racc_print(2, BLOD"PROMPT"MINT" Syntax error near pipe\n");
		return (1);
	}
	else if (node->type == PIPE && node->next->type == PIPE)
	{
		racc_print(2, BLOD"PROMPT"MINT" Syntax error near pipe\n");
		return (1);
	}
	return (0);
}
