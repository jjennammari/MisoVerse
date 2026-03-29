/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miso_expand.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jemustaj <jemustaj@student.42Porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/07 19:06:05 by jemustaj          #+#    #+#             */
/*   Updated: 2026/03/17 01:06:11 by jemustaj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/miso.h"

int		miso_expand(t_shell *miso);
char	*miso_exp_without_quotes(t_shell *miso, char *str);
char	*miso_exp_exit_code(t_shell *miso, char *res, int *pi);
char	*miso_exp_env(t_shell *miso, char *res, char *str, int *pi);
char	*miso_get_exp_name(t_shell *miso, char *str, int *pi);

int	miso_expand(t_shell *miso)
{
	t_token	*temp;

	temp = miso->list.head;
	while (temp)
	{
		if (temp->expand == 1 && /*(*/temp->quotes == 1/* || miso_is_command(temp->type))*/)
		{
			miso_expand_quotes(miso, temp);
			miso->list.squote = 0;
			miso->list.dquote = 0;
		}
		else if (temp->expand == 1 && temp->quotes == 0)
			miso_expand_node(miso, temp);
		temp = temp->next;
	}
	if (miso_find_empty_str(miso))
		return (1);
	miso_remove_extra_quotes(miso);
	return (0);
}

char	*miso_exp_without_quotes(t_shell *miso, char *str)
{
	char	*res;
	int		i;

	res = miso_allocate_str(miso, 1);
	i = 0;
	while (str[i])
	{
		if (str[i] == '$')
		{
			if (str[i] == '$' && str[i + 1] == '?')
				res = miso_exp_exit_code(miso, res, &i);
			else if (str[i] == '$' && str[i + 1] != '?')
				res = miso_exp_env(miso, res, &str[i], &i);
			continue ;
		}
		res = miso_sub_add_str(miso, res, &str[i], &i);
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
	exp = miso_add_str_str(miso, res, code);
	free(code);
	*pi += 2;
	return (exp);
}

char	*miso_exp_env(t_shell *miso, char *res, char *str, int *pi)
{
	char	*exp;
	char	*exp_part;
	char	*exp_name;
	int		i;

	i = 0;
	exp_name = miso_get_exp_name(miso, &str[i], pi);
	if (!exp_name)
		exp = miso_add_str_str(miso, res, "$");
	else
	{
		exp_part = miso_getenv(exp_name, miso->envp);
		exp = miso_add_str_str(miso, res, exp_part);
	}
	free(exp_name);
	return (exp);
}

char	*miso_get_exp_name(t_shell *miso, char *str, int *pi)
{
	char	*name;
	int		len;

	len = 1;
	while (str[len] && (ft_isalnum(str[len]) || str[len] == '_'))
		len++;
	*pi += len;
	if (len == 1)
		return (NULL);
	name = ft_substr(str, 1, len - 1);
	if (!name)
		misoverse_free_exit(miso, 1, 2);
	return (name);
}
