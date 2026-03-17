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
int		miso_remove_empty_nodes(t_shell *miso);
char	*miso_allocate_str(t_shell *miso, size_t len);
char	*miso_sub_add_str(t_shell *miso, char *s1, char *s2, int *pi);
//char	*miso_subtract_exp_name(t_shell *miso, char *str, int len);

int	miso_expand_node(t_shell *miso, t_token *node)
{
	char	*res;

	res = miso_exp_without_quotes(miso, node->str);
	free(node->str);
	node->str = res;
	node->expand = 0;
	return (0);
}

int	miso_remove_empty_nodes(t_shell *miso)
{
	t_token	*temp;
	t_token	*delete;

	while (miso->list.head && miso->list.head->str == NULL)
	{
		delete = miso->list.head;
		miso->list.head = delete->next;
		free(delete);
	}
	temp = miso->list.head;
	while (temp->next)
	{
		if (temp->next->str == NULL)
		{
			delete = temp->next;
			temp->next = delete->next;
			free(delete);
		}
		else
			temp = temp->next;
	}
	if (miso->list.head == NULL)
		return (1);
	return (0);
}

char	*miso_allocate_str(t_shell *miso, size_t len)
{
	char	*res;

	res = ft_calloc(len, sizeof(char));
	if (!res)
		misoverse_free_exit(miso, 1, 2);
	return (res);
}

char	*miso_sub_add_str(t_shell *miso, char *s1, char *s2, int *pi)
{
	char	*temp;
	char	*new;
	int		len;

	len = 0;
	while (s2[len] && s2[len] != '$')
		len++;
	*pi += len;
	temp = ft_substr(s2, 0 , len);
	if (!temp)
		misoverse_free_exit(miso, 1 ,2);
	if (!s1 || !*s1)
		return (temp);
	new = miso_add_str_str(miso, s1, temp);
	free(temp);
	return (new);
}
/*
char	*miso_subtract_exp_name(t_shell *miso, char *str, int len)
{
	char	*res;
	int		i;

	res = miso_allocate_str(miso, len + 1);
	i = 0;
	while (i < len)
	{
		res[i] = str[i];
		i++;
	}
	res[i] = '\0';
	return (res);
}*/
