/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miso_tokenize_utils_beta.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jemustaj <jemustaj@student.42Porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/16 23:58:08 by jemustaj          #+#    #+#             */
/*   Updated: 2026/03/17 00:49:54 by jemustaj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/miso.h"

int		miso_skip_whitespaces(char *line);
int		miso_is_whitespace(char c);
char	*miso_add_char_str(t_shell *miso, char *str, char c);
char	*miso_convert_char_as_str(t_shell *miso, char c);
char	*miso_add_str_str(t_shell *miso, char *s1, char *s2);

int	miso_skip_whitespaces(char *line)
{
	int	i;

	i = 0;
	if (miso_is_whitespace(line[i]))
	{
		while (line[i] && miso_is_whitespace(line[i]))
			i++;
		if (line[i] == '\0')
			return (1);
		else
			return (0);
	}
	return (0);
}

int	miso_is_whitespace(char c)
{
	if (c == 32 || (c >= 9 && c <= 13))
		return (1);
	return (0);
}

char	*miso_add_char_str(t_shell *miso, char *str, char c)
{
	char	*res;
	char	*temp;

	temp = miso_convert_char_as_str(miso, c);
	if (!temp)
		misoverse_free_exit(miso, 1, 2);
	res = miso_add_str_str(miso, str, temp);
	free(temp);
	return (res);
}

char	*miso_convert_char_as_str(t_shell *miso, char c)
{
	char	*res;

	res = miso_allocate_str(miso, 2);
	res[0] = c;
	return (res);
}

char	*miso_add_str_str(t_shell *miso, char *s1, char *s2)
{
	char	*res;
	int		len;

	if (!s2)
		return (s1);
	len = ft_strlen(s2);
	if (!s1 || !*s1)
		res = ft_substr(s2, 0, len);
	else
		res = ft_strjoin(s1, s2);
	if (!res)
		misoverse_free_exit(miso, 1, 2);
	if (s1)
		free(s1);
	return (res);
}
