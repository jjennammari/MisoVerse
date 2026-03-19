/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miso_tokenize_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jemustaj <jemustaj@student.42Porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/29 22:48:35 by jemustaj          #+#    #+#             */
/*   Updated: 2026/03/17 00:06:07 by jemustaj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/miso.h"

void	miso_tokenize_redirections(t_shell *miso, char *str, int *pi);
void	miso_build_token_list(t_shell *miso, char *str, t_token_type type);
void	miso_init_newnode(t_shell *miso, t_token *new_node,\
					char *str, t_token_type type);

void	miso_tokenize_redirections(t_shell *miso, char *line, int *pi)
{
	int	i;

	i = 0;
	if (line[i] == '<')
	{
		if (line[i + 1] == '<')
		{
			miso_build_token_list(miso, ft_strdup("<<"), HEREDOC);
			miso->list.hd_count += 1;
			*pi += 1;
		}
		else
			miso_build_token_list(miso, ft_strdup("<"), RD_IN);
	}
	else if (line[i] == '>')
	{
		if (line[i + 1] == '>')
		{
			miso_build_token_list(miso, ft_strdup(">>"), APPEND);
			*pi += 1;
		}
		else
			miso_build_token_list(miso, ft_strdup(">"), RD_OUT);
	}
	*pi += 1;
}

void	miso_build_token_list(t_shell *miso, char *str, t_token_type type)
{
	t_token	*new_node;

	if (!str)
		misoverse_free_exit(miso, 1, 2);
	new_node = malloc(sizeof(t_token));
	if (!new_node)
		misoverse_free_exit(miso, 1, 2);
	miso_init_newnode(miso, new_node, str, type);
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

void	miso_init_newnode(t_shell *miso, t_token *new_node, char *str,\
					t_token_type type)
{
	new_node->expand = 0;
	new_node->quotes = 0;
	new_node->str = str;
	new_node->type = type;
	new_node->next = NULL;
	if (miso->node->quotes == 1)
		new_node->quotes = 1;
	if (miso->node->expand == 1)
		new_node->expand = 1;
	miso->node->expand = 0;
	miso->node->quotes = 0;
}
