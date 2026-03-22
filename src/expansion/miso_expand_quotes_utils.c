/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miso_expand_quotes_utils.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jemustaj <jemustaj@student.42Porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/17 00:14:51 by jemustaj          #+#    #+#             */
/*   Updated: 2026/03/17 00:20:23 by jemustaj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/miso.h"

void	miso_remove_extra_quotes(t_shell *miso);
char	*miso_remove_quotes(t_shell *miso, char *str);
char	*miso_del_squotes(t_shell *miso, char *res, char *str, int *pi);
char	*miso_del_dquotes(t_shell *miso, char *res, char *str, int *pi);

void	miso_remove_extra_quotes(t_shell *miso)
{
	t_token	*temp;
	char	*res;

	temp = miso->list.head;
	while (temp)
	{
		if (temp->quotes == 1)
		{
			res = miso_remove_quotes(miso, temp->str);
			free(temp->str);
			temp->str = res;
		}
		temp = temp->next;
	}
}

char	*miso_remove_quotes(t_shell *miso, char *str)
{
	char	*res;
	int		i;

	res = miso_allocate_str(miso, 1);
	if (str[0] == '\'' && str[1] == '\'' && str[2] == '\0')
		return (res);
	if (str[0] == '"' && str[1] == '"' && str[2] == '\0')
		return (res);
	i = 0;
	while (str[i])
	{
		if (str[i] == '\'')
			res = miso_del_squotes(miso, res, &str[i], &i);
		else if (str[i] == '"')
			res = miso_del_dquotes(miso, res, &str[i], &i);
		while (str[i] && !ft_strchr("'\"", str[i]))
		{
			res = miso_add_char_str(miso, res, str[i]);
			i++;
		}
	}
	return (res);
}

char	*miso_del_squotes(t_shell *miso, char *res, char *str, int *pi)
{
	char	*temp;
	int		len;

	len = 1;
	while (str[len] && str[len] != '\'')
		len++;
	*pi += len + 1;
	if (len == 1)
		return (miso_add_str_str(miso, res, NULL));
	temp = ft_substr(str, 1, len - 1);
	if (!temp)
		misoverse_free_exit(miso, 1, 2);
	res = miso_add_str_str(miso, res, temp);
	free(temp);
	return (res);
}

char	*miso_del_dquotes(t_shell *miso, char *res, char *str, int *pi)
{
	char	*temp;
	int		len;

	len = 1;
	while (str[len] && str[len] != '"')
		len++;
	*pi += len + 1;
	if (len == 1)
		return (miso_add_str_str(miso, res, NULL));
	temp = ft_substr(str, 1, len - 1);
	if (!temp)
		misoverse_free_exit(miso, 1, 2);
	res = miso_add_str_str(miso, res, temp);
	free(temp);
	return (res);
}
