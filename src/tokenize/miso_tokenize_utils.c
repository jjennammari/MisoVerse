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

#include "../../inc/miso.h"

void	miso_build_token_list(t_shell *miso, char *str, t_token_type type);
void	miso_init_newnode(t_shell *miso, t_token *new_node, char *str, t_token_type type);
int		miso_is_whitespace(char c);
char	*miso_add_char_to_str(t_shell *miso, char *str, char c);
char	*miso_convert_char_as_str(t_shell *miso, char c);
char	*miso_add_str(t_shell *miso, char *s1, char *s2);

void	miso_build_token_list(t_shell *miso, char *str, t_token_type type)
{
	t_token	*new_node;

	if (!str)
		misoverse_free_exit(miso, 1 ,2);
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

void	miso_init_newnode(t_shell *miso, t_token *new_node, char *str, t_token_type type)
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

int	miso_is_whitespace(char c)
{
	if (c == 32 || (c >= 9 && c <= 13))
		return (1);
	return (0);
}

char	*miso_add_char_to_str(t_shell *miso, char *str, char c)
{
	char	*res;
	char	*temp;

	res = miso_allocate_str(miso, (ft_strlen(str) + 2));
	temp = miso_convert_char_as_str(miso, c);
	if (!temp)
		misoverse_free_exit(miso, 1, 2);
	res = ft_strjoin(str, temp);
	if (!res)
		misoverse_free_exit(miso, 1, 2);
	free(temp);
	if (str)
		free(str);
	return (res);
}

char	*miso_convert_char_as_str(t_shell *miso, char c)
{
	char	*res;

	res = miso_allocate_str(miso, 2);
	res[0] = c;
	return (res);
}

char	*miso_add_str(t_shell *miso, char *s1, char *s2)
{
	char	*res;
	int		len;

	if (!s2)
		return (s1);
	len = ft_strlen(s2);
	if (!s1 || !*s1)
		res = ft_substr(s2, 0 , len);
	else
		res = ft_strjoin(s1, s2);
	if (!res)
		misoverse_free_exit(miso, 1 ,2);
	if (s1)
		free(s1);
	return (res);
}
