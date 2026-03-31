/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miso_expand_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jemustaj <jemustaj@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/11 21:52:30 by jemustaj          #+#    #+#             */
/*   Updated: 2026/03/17 01:05:05 by jemustaj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/miso.h"

int		miso_expand_node(t_shell *miso, t_token *node);
int		miso_find_empty_str(t_shell *miso);
void	miso_set_str_null(t_shell *miso, int change);
void	miso_delete_empty_str(t_shell *miso, t_token **node, int del);
char	*miso_allocate_str(t_shell *miso, size_t len);

int	miso_expand_node(t_shell *miso, t_token *node)
{
	char	*res;
	char	**words;

	res = miso_exp_without_quotes(miso, node->str);
	free(node->str);
	node->str = res;
	node->expand = 0;
	words = miso_exp_split(miso, node->str);
	if (words && words[0])
		miso_add_exp_words(miso, node, words);
	if (words)
		miso_free_matrix(words);
	return (0);
}

int	miso_find_empty_str(t_shell *miso)
{
	t_token	*node;
	char	*str;
	int		modify;

	node = miso->list.head;
	modify = 0;
	while (node)
	{
		str = node->str;
		if (miso_is_redirection(node->type) && node->quotes == 0)
			miso_set_str_null(miso, modify + 1);
		else if (node->str && node->quotes == 0 && str[0] == '\0')
		{
			miso_delete_empty_str(miso, &node, modify);
			continue ;
		}
		modify++;
		node = node->next;
	}
	if (miso->list.head == NULL)
		return (1);
	if (!(miso_is_redirection(miso->list.head->type)))
		miso_set_commandtype(miso->list.head);
	return (0);
}

void	miso_set_str_null(t_shell *miso, int change)
{
	t_token	*node;
	char	*str;
	int		count;

	node = miso->list.head;
	count = 0;
	while (count < change)
	{
		node = node->next;
		count++;
	}
	str = node->str;
	if (str[0] == '\0')
	{
		free(node->str);
		node->str = NULL;
	}
}

void	miso_delete_empty_str(t_shell *miso, t_token **node, int del)
{
	t_token	*temp;
	int		count;

	temp = miso->list.head;
	if (temp == (*node))
	{
		miso_delete_node(node);
		miso->list.head = NULL;
	}
	count = 0;
	while (count < del - 1)
	{
		temp = temp->next;
		count++;
	}
	temp->next = temp->next->next;
	miso_delete_node(node);
	(*node) = temp;
}

char	*miso_allocate_str(t_shell *miso, size_t len)
{
	char	*res;

	res = ft_calloc(len, sizeof(char));
	if (!res)
		misoverse_free_exit(miso, 1, 2);
	return (res);
}
