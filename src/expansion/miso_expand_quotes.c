/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miso_expand_quotes.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jemustaj <jemustaj@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/14 22:26:33 by jemustaj          #+#    #+#             */
/*   Updated: 2026/03/14 22:28:01 by jemustaj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/miso.h"

void	miso_expand_quotes(t_shell *miso, t_token *node, char *str);
char	*miso_exp_with_quotes(t_shell *miso, t_token *node, char *str);
void	miso_validate_expansion(t_shell *miso, t_token *node, char c);
void	miso_update_quotes(t_shell *miso, char c);
void	miso_remove_surroundign_quotes(t_shell *miso);
char	*miso_remove_quotes(t_shell *miso, t_token *node, char *str);
char	*miso_remove_squotes(t_shell *miso, char *res, char *str, int *pi);
char	*miso_remove_dquotes(t_shell *miso, char *res, char *str, int *pi);
char	*miso_add_str(t_shell *miso, char *s1, char *s2);

void	miso_expand_quotes(t_shell *miso, t_token *node, char *str)
{
	char	*res;

	res = miso_exp_with_quotes(miso, node, str);
	free(node->str);
	node->str = res;
	node->expand = 0;
}

char	*miso_exp_with_quotes(t_shell *miso, t_token *node, char *str)
{
	char	*res;
	int		i;

	res = miso_allocate_str(miso, 1);
	i = 0;
	while (str[i])
	{
		if (str[i] == '\'' || str[i] == '"')
			miso_validate_expansion(miso, node, str[i]);
		if (str[i] == '$' && node->expand == 1)
		{
			if (str[i + 1] == '?')
				res = miso_exp_exit_code(miso, res, &i);
			else
				res = miso_exp_env(miso, res, &str[i], &i);
		}
		while (str[i] && node->expand == 0)
		{
			if (str[i] == '\'' || str[i] == '"')
				miso_validate_expansion(miso, node, str[i]);
			res = miso_add_char_to_str(miso, res, str[i]);
			i++;
		}
	}
	return (res);
}

void	miso_validate_expansion(t_shell *miso, t_token *node, char c)
{
	if (c == '\'' && miso->list.dquote == 0)
	{
		node->expand = 0;
		miso_update_quotes(miso, c);
	}
	else if (c == '\'' && miso->list.dquote == 1)
	{
		node->expand = 1;
		miso_update_quotes(miso, c);
	}
	else if (c == '"' && miso->list.squote == 0)
	{
		node->expand = 1;
		miso_update_quotes(miso, c);
	}
	else if (c == '"' && miso->list.squote == 1)
	{
		node->expand = 0;
		miso_update_quotes(miso, c);
	}
}

void	miso_update_quotes(t_shell *miso, char c)
{
	if (c == '\'')
	{
		if (miso->list.squote == 0)
			miso->list.squote = 1;
		else if (miso->list.squote == 1)
			miso->list.squote = 0;
	}
	else if (c == '"')
	{
		if (miso->list.dquote == 0)
			miso->list.dquote = 1;
		else if (miso->list.dquote == 1)
			miso->list.dquote = 0;
	}
}

void	miso_remove_surrounding_quotes(t_shell *miso)
{
	t_token	*temp;
	char	*res;

	while (temp)
	{
		if (temp->quotes == 1)
		{
			res = miso_remove_quotes(miso, temp, temp->str);
			free(temp->str);
			temp->str = res;
		}
	}
}

char	*miso_remove_quotes(t_shell *miso, t_token *node, char *str)
{
	char	*temp;
	char	*res;
	int		i;

	res = miso_allocate_str(miso, 1);
	i = 0;
	while (str[i])
	{
		if (str[i] == '\'')
		{
			res = miso_remove_squotes(miso, res, &str[i], &i);
		}
		else if (str[i] == '"')
		{
			res = miso_remove_dquotes(miso, res, &str[++i], &i);
		}
		while (str[i] && !ft_strchr("'\"", str[i]))
		{
			res = miso_add_char_to_str(miso, res, str[i]);
			i++;
		}
	}
	return (res);
}

char	*miso_remove_squotes(t_shell *miso, char *res, char *str, int *pi)
{
	char	*temp;
	int		len;

	len = 0;
	while (str[len] != '\'')
		len++;
	if (len == 0)
	{
		res = ft_strdup("''");
		if (!res)
		  misoverse_free_exit(miso, 1, 2);
		*pi += 1;
		return (res);
	}
	temp = ft_substr(str, 0, len);
	if (!temp)
		misoverse_free_exit(miso, 1, 2);
	res = miso_add_str(miso, res, temp);
	*pi += len + 1;
	return (res);
}

char	*miso_remove_dquotes(t_shell *miso, char *res, char *str, int *pi)
{
	char	*temp;
	int		len;

	len = 0;
	while (str[len] != '"')
		len++;
	if (len == 0)
	{
		res = ft_strdup("\"\"");
		if (!res)
		  misoverse_free_exit(miso, 1, 2);
		*pi += 1;
		return (res);
	}
	temp = ft_substr(str, 0, len);
	if (!temp)
		misoverse_free_exit(miso, 1, 2);
	res = miso_add_str(miso, res, temp);
	*pi += len + 1;
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
