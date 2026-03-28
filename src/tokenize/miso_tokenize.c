/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miso_tokenize.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jemustaj <jemustaj@student.42Porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/29 22:47:33 by jemustaj          #+#    #+#             */
/*   Updated: 2026/03/17 00:09:19 by jemustaj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/miso.h"

int		miso_tokenize(t_shell *miso, char *line);
void	miso_tokenize_operators(t_shell *miso, char *str, int *pi);
void	miso_tokenize_arguments(t_shell *miso, char *str, int *pi);
char	*miso_tokenize_squotes(t_shell *miso, char *res, char *line, int *pi);
char	*miso_tokenize_squotes(t_shell *miso, char *res, char *line, int *pi);

int	miso_tokenize(t_shell *miso, char *line)
{
	int		i;

	if (miso_skip_whitespaces(line))
		return (1);
	i = 0;
	while (line[i])
	{
		if (miso->list.last_node && miso->list.last_node->type == HEREDOC &&
				line[i] == '-')
			miso->node->valid_delim = 1;
		while (line[i] && miso_is_whitespace(line[i]))
			i++;
		if (line[i] == '\0')
			break ;
		if (ft_strchr("<|>", line[i]))
			miso_tokenize_operators(miso, &line[i], &i);
		else
			miso_tokenize_arguments(miso, &line[i], &i);
	}
	return (0);
}

void	miso_tokenize_operators(t_shell *miso, char *line, int *pi)
{
	int	i;

	i = 0;
	if (line[i] == '|')
	{
		miso_build_token_list(miso, ft_strdup("|"), PIPE);
		*pi += 1;
	}
	else
		miso_tokenize_redirections(miso, line, pi);
}

void	miso_tokenize_arguments(t_shell *miso, char *line, int *pi)
{
	char	*t_str;
	int		i;

	t_str = miso_allocate_str(miso, 1);
	i = 0;
	while (line[i] && !miso_is_whitespace(line[i])
		&& !ft_strchr("<|>", line[i]))
	{
		if (line[i] == '\'')
			t_str = miso_tokenize_squotes(miso, t_str, &line[i],
					&i);
		else if (line[i] == '"')
			t_str = miso_tokenize_dquotes(miso, t_str, &line[i],
					&i);
		else
			t_str = miso_tokenize_words(miso, t_str, &line[i], &i);
	}
	*pi += i;
	miso_build_token_list(miso, t_str, ARG);
}

char	*miso_tokenize_squotes(t_shell *miso, char *res, char *line, int *pi)
{
	char	*temp;
	char	*t_str;
	int		len;

	len = 1;
	while (line[len] && line[len] != '\'')
	{
		if (line[len] == '$' && line[0] != '\'' && miso->node->expand == 0)
			miso->node->expand = 1;
		len++;
	}
	len++;
	temp = ft_substr(line, 0, len);
	if (!temp)
		misoverse_free_exit(miso, 1, 2);
	t_str = miso_add_str_str(miso, res, temp);
	free(temp);
	miso->node->quotes = 1;
	*pi += len;
	return (t_str);
}

char	*miso_tokenize_dquotes(t_shell *miso, char *res, char *line, int *pi)
{
	char	*temp;
	char	*t_str;
	int		len;

	len = 1;
	while (line[len] && line[len] != '"')
	{
		if (line[len] == '$' && line[0] != '\'' && miso->node->expand == 0)
			miso->node->expand = 1;
		len++;
	}
	len++;
	temp = ft_substr(line, 0, len);
	if (!temp)
		misoverse_free_exit(miso, 1, 2);
	t_str = miso_add_str_str(miso, res, temp);
	free(temp);
	miso->node->quotes = 1;
	*pi += len;
	return (t_str);
}
