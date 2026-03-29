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
void	miso_init_newnode(t_shell *miso, t_token *new_node,
			char *str, t_token_type type);
char	*miso_sub_add_str(t_shell *miso, char *s1, char *s2, int *pi);

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

char	*miso_tokenize_words(t_shell *miso, char *res, char *line, int *pi)
{
	char	*temp;
	char	*t_str;
	int		len;

	len = 0;
	while (line[len] && !miso_is_whitespace(line[len])
		&& !ft_strchr("<|>'\"", line[len]))
	{
		if (line[len] == '$' && miso->node->expand == 0)
			miso->node->expand = 1;
		len++;
	}
	temp = ft_substr(line, 0, len);
	if (!temp)
		misoverse_free_exit(miso, 1, 2);
	t_str = miso_add_str_str(miso, res, temp);
	free(temp);
	*pi += len;
	return (t_str);
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
	new_node->valid_delim = 0;
	new_node->str = str;
	new_node->type = type;
	new_node->next = NULL;
	if (miso->node->quotes == 1)
		new_node->quotes = 1;
	if (miso->node->expand == 1)
		new_node->expand = 1;
	if (miso->node->valid_delim == 1)
		new_node->valid_delim = 1;
	miso->node->expand = 0;
	miso->node->quotes = 0;
	miso->node->valid_delim = 0;
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
	temp = ft_substr(s2, 0, len);
	if (!temp)
		misoverse_free_exit(miso, 1, 2);
	if (!s1 || !*s1)
		return (temp);
	new = miso_add_str_str(miso, s1, temp);
	free(temp);
	return (new);
}
