/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miso_expand_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jemustaj <jemustaj@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/11 21:52:30 by jemustaj          #+#    #+#             */
/*   Updated: 2026/03/11 22:42:51 by jemustaj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/miso.h"

char	*miso_allocate_str(t_shell *miso, size_t len)
{
	char	*res;

	res = malloc(sizeof(char) * len);
	if (!res)
		misoverse_free_exit(miso, 1, 2);
	res[1] = '\0';
	return (res);
}

char	*miso_add_to_str(t_shell *miso, char *s1, char *s2)
{
	char	*res;
	int		i;

	i = 0;
	while (s2[i] || s2[i] != '$')
		i++;
	res = ft_strjoin(s1, &s2[i]);
	if (!res)
		misoverse_free_exit(miso, 1 ,2);
	if (s1)
		free(s1);
	return (res);
}

char	*miso_get_exp_name(t_shell *miso, char *str, int *pi)
{
	char	*name;
	int		len;

	len = 1;
	while (str[len] && (ft_isalnum(str[len]) || str[len] == '-'))
		len++;
	if (len == 1)
		return (NULL);
	name = miso_subtract_exp_name(miso, &str[1], len - 1);
	*pi += len - 1;
	return (name);
}

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
}
