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
void	miso_mark_quotes(t_shell *miso, t_token *new_node);
void	miso_mark_expansion(t_shell *miso, t_token *new_node);
int		miso_is_whitespace(char c);
int		miso_skip_empty_quotes(char *line, int *pi);
char	*miso_char_to_str(t_shell *miso, char *str, char c);

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
		miso_mark_quotes(miso, new_node);
	if (miso->node->expand == 1)
		miso_mark_expansion(miso, new_node);
	miso->node->expand = 0;
	miso->node->quotes = 0;
}

void	miso_mark_quotes(t_shell *miso, t_token *new_node)
{
	new_node->quotes = 1;
	miso->node->quotes = 0;
}

void	miso_mark_expansion(t_shell *miso, t_token *new_node)
{
	new_node->expand = 1;
	miso->node->expand = 0;
}

int	miso_is_whitespace(char c)
{
	if (c == 32 || (c >= 9 && c <= 13))
		return (1);
	return (0);
}

int	miso_skip_empty_quotes(char *line, int *pi)
{
	if (miso_is_squote(line[0]) && miso_is_squote(line[1]))
	{
		*pi += 2;
		return (1);
	}
	else if (miso_is_dquote(line[0]) && miso_is_dquote(line[1]))
	{
		*pi += 2;
		return (1);
	}
	return (0);
}

char	*miso_char_to_str(t_shell *miso, char *str, char c)
{
	char	*res;
	char	*temp;

	res = miso_allocate_str(miso, (ft_strlen(str) + 2));
	temp = ft_strdup(&c);
	if (!temp)
		misoverse_free_exit(miso, 1, 2);
	res = ft_strjoin(res, temp);
	if (!res)
		misoverse_free_exit(miso, 1, 2);
	free(temp);
	free(str);
	return (res);
}
