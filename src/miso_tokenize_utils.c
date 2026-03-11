/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miso_tokenize_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jemustaj <jemustaj@student.42Porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/29 22:48:35 by jemustaj          #+#    #+#             */
/*   Updated: 2026/03/08 22:25:38 by lde-san-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/miso.h"

int	miso_is_whitespace(char c)
{
	if (c == 32 || (c >= 9 && c <= 13))
		return (1);
	return (0);
}

void	miso_mark_quotes(t_shell *miso, t_token *new_node)
{
	new_node->is_quotet = 1;
	miso->node->is_quotet = 0;
}

void	miso_mark_expansion(t_shell *miso, t_token *new_node)
{
	new_node->expand = 1;
	miso->node->expand = 0;
}

void	miso_init_newnode(t_shell *miso, t_token *new_node, char *str, t_token_type type)
{
	new_node->str = str;
	new_node->type = type;
	new_node->is_quotet = 0;
	new_node->expand = 0;
	new_node->next = NULL;
	if (miso->node->is_quotet == 1)
		miso_mark_quotes(miso, new_node);
	if (miso->node->expand == 1)
		miso_mark_expansion(miso, new_node);
}
