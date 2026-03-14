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

#include "../../inc/miso.h"

char	*miso_expand(t_shell *miso, char *str);
char	*miso_exp_exit_code(t_shell *miso, char *res, int *pi);
char	*miso_exp_env(t_shell *miso, char *res, char *str, int *pi);

char	*miso_expand(t_shell *miso, char *str)
{
	char	*res;
	int		i;

	res = miso_allocate_str(miso, 1);
	i = 0;
	while (str[i])
	{
		if (ft_strchr("'\"", str[i]))
			miso_update_quotes(miso, str[i]);
		if (str[i + 1] == '?' && miso->list.dquote == 1)
			res = miso_exp_exit_code(miso, res, &i);
		else if (str[i] == '$' && str[i + 1] != '?' && miso->list.dquote == 1)
			res = miso_exp_env(miso, res, &str[i], &i);
		else
		{
			res = miso_str_to_str(miso, res, &str[i]);
			i = ft_strlen(res) - 1;
		}
		i++;
	}
	return (res);
}

char	*miso_exp_exit_code(t_shell *miso, char *res, int *pi)
{
	char	*code;
	char	*exp;

	code = ft_itoa(miso->exit_code);
	if (!code)
		misoverse_free_exit(miso, 1, 2);
	exp = miso_str_to_str(miso, res, code);
	free(code);
	*pi += 1;
	return (exp);
}

char	*miso_exp_env(t_shell *miso, char *res, char *str, int *pi)
{
	char	*exp;
	char	*exp_part;
	char	*exp_name;


	exp_name = miso_get_exp_name(miso, &str[*pi], pi);
	if (!exp_name)
		exp = miso_str_to_str(miso, res, "$");
	else
	{
		exp_part = miso_getenv(exp_name, miso->envp);
		if (!exp_part)//TODO: move pi
		{
			free(exp_name);
			return (res);
		}
		exp = miso_str_to_str(miso, res, exp_part);
	}
	free(exp_name);
	return (exp);
}
