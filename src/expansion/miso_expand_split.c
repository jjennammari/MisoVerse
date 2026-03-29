/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miso_expand_split.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jemustaj <jemustaj@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/28 22:20:00 by jemustaj          #+#    #+#             */
/*   Updated: 2026/03/28 22:49:41 by jemustaj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/miso.h"

char	**miso_exp_split(t_shell *miso, char *str);
int		miso_count_words(char *str);
void	miso_fill_words(t_shell *miso, char **words, char *str);
void	miso_add_exp_words(t_shell *miso, t_token *node, char **words);
void	miso_add_exp_nodes(t_shell *miso, t_token *node, char *word);

char	**miso_exp_split(t_shell *miso, char *str)
{
	char	**words;
	int		w_count;

	w_count = miso_count_words(str);
	words = ft_calloc((w_count + 1), sizeof(char *));
	if (!words)
		misoverse_free_exit(miso, 1, 2);
	miso_fill_words(miso, words, str);
	return (words);
}

int	miso_count_words(char *str)
{
	int	i;
	int	count;

	count = 0;
	i = 0;
	while (str[i])
	{
		while (str[i] && miso_is_whitespace(str[i]))
			i++;
		if (str[i] == '\0')
			break ;
		while (str[i] && !miso_is_whitespace(str[i]))
			i++;
		count++;
	}
	return (count);
}

void	miso_fill_words(t_shell *miso, char **words, char *str)
{
	int	i;
	int	j;
	int	start;

	j = 0;
	i = 0;
	while (str && str[i])
	{
		while (str[i] && miso_is_whitespace(str[i]))
			i++;
		if (str[i] == '\0')
			break ;
		start = i;
		while (str[i] && !miso_is_whitespace(str[i]))
			i++;
		words[j] = ft_substr(str, start, i - start);
		if (!words[j])
			misoverse_free_exit(miso, 1, 2);
		j++;
	}
	words[j] = NULL;
}

void	miso_add_exp_words(t_shell *miso, t_token *node, char **words)
{
	char	*first;
	int		i;

	first = ft_strdup(words[0]);
	if (!first)
		misoverse_free_exit(miso, 1, 2);
	free(node->str);
	node->str = first;
	i = 1;
	while (words[i])
	{
		miso_add_exp_nodes(miso, node, words[i]);
		node = node->next;
		i++;
	}
}

void	miso_add_exp_nodes(t_shell *miso, t_token *node, char *word)
{
	t_token	*new_node;
	char	*new_word;

	if (!node || !word)
		return ;
	new_word = ft_strdup(word);
	if (!new_word)
		misoverse_free_exit(miso, 1, 2);
	new_node = malloc(sizeof(t_token));
	if (!new_node)
		misoverse_free_exit(miso, 1, 2);
	miso_init_newnode(miso, new_node, new_word, ARG);
	new_node->next = node->next;
	node->next = new_node;
	if (miso->list.last_node == node)
		miso->list.last_node = new_node;
}
