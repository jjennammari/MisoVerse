/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miso_parser.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jemustaj <jemustaj@student.42Porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/12 22:48:03 by jemustaj          #+#    #+#             */
/*   Updated: 2026/02/13 13:45:24 by jemustaj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	miso_parse(t_shell *miso)
{
	if (parse_redirections(miso))
		return (1);
	if (parse_pipe(miso))
		return (1);
	return (0);
}

int	parse_redirections(t_shell *miso)
{
	if (
	return (0);
}

int	parse_pipe(t_shell *miso)
{
	t_token	*temp;

	if (miso->list.head->type == PIPE || miso->list.last_node->type == PIPE)
	{
		//print error message
		return (1);
	}
	temp = miso->list.head;
	while (temp)
	{
		if (temp->type == PIPE && temp->next->type == PIPE)
		{
			//print error message
			return (1);
		}
		if (temp->type == PIPE && temp->next->type == ARG)
			set_commandtype(temp->next);
		temp = temp->next;
	}
	return (0);
}
