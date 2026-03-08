/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miso_expand.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jemustaj <jemustaj@student.42Porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/07 19:06:05 by jemustaj          #+#    #+#             */
/*   Updated: 2026/03/08 22:26:24 by lde-san-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/miso.h"

char	*miso_expand(t_shell *miso, char *str)
{
	char	*res;
	char	*exp;
	char	*exp_name;
	int		i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '$')
		{
			exp_name = miso_get_exp_name(miso, &str[i], &i);
			if (!exp_name)
				res = miso_add_to_str(res, "$");
			else
			{
				exp = miso_getenv(exp_name, miso->envp);
				res = miso_add_to_str(res, exp);
				free(exp_name);
			}
		}
		else
			res = miso_add_to_str(res, &str[i]);
		i++;
	}
	return (res);
}

char	*miso_get_exp_name(t_shell *miso, char *str, int *pi)
{
	char	*name;
	int		len;

	if (str[*pi++] == '?')
	{
		*pi += 1;
		return (ft_itoa(miso->exit_code));
	}
	len = 1;
	while (str[len] && (miso_is_alnum(str[len]) || str[len] == '-'))
		len++;
	if (len == 1)
		return (NULL);
	name = miso_subtract_exp_name(str, len);
	*pi += len - 1;
	return (name);
}

char	*miso_subtract_exp_name(char *str, int len)
{
	char	*res;
	int		i;

	res = malloc(sizeof(char) * len + 1);
	if (!res)
	{
		perror(BLOD"PROMPT"MINT);
		//function to free and exit from mapache
	}
	i = 0;
	while (i < len)
	{
		res[i] = str[i];
		i++;
	}
	res[i] = '\0';
	return (res);
}

char	*miso_add_to_str(char *s1, char *s2)
{
	char	*res;

	res = ft_strjoin(s1, s2);
	if (!res)
	{
		perror(BLOD"PROMPT"MINT);
		// function to free and exit from mapache
	}
	if (s1)
		free(s1);
	return (res);
}

void	miso_expand_node(t_shell *miso, t_token *node, char *str)
{
	char	*res;

	res = miso_expand(miso, str);
	free(node->str);
	node->str = res;
	node->expand = 0;
}

char	*miso_expand_line(t_shell *miso, char *line)
{
	char	*res;

	res = miso_expand(miso, line);
	if (!res)
		return (NULL);
	return (res);
}

int	miso_is_alnum(char c)
{
	if ((c >= 65 && c <= 90) || (c >= 97 && c <= 122) || (c >= 48 && c <= 57))
		return (1);
	return (0);
}
