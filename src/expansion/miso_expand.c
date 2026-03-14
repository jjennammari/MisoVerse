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

void	miso_expansion(t_shell *miso);
int		miso_expand_node(t_shell *miso, t_token *node, char *str);
char	*miso_expand(t_shell *miso, char *str);
char	*miso_exp_exit_code(t_shell *miso, char *res, int *pi);
char	*miso_exp_env(t_shell *miso, char *res, char *str, int *pi);

int	miso_expansion(t_shell *miso)
{
	t_token	*temp;

	temp = miso->list.head;
	while (temp)
	{
		if (temp->expand == 1 && temp->quotes == 1)
			miso_expand_quotes(miso, temp, temp->str);
		else if (temp->expand == 1 && temp->quotes == 0)
			miso_expand_node(miso, temp, temp->str);
	}
	miso_remove_extra_quotes(miso);//NOTE: leave nodes with only "" or '' as args
	if (miso_remove_empty_nodes(miso))
		return (1);
	return (0);
}

int	miso_expand_node(t_shell *miso, t_token *node, char *str)
{
	char	*res;

	res = miso_expand(miso, str);
	free(node->str);
	node->str = res;
	node->expand = 0;
	return (0);
}

int	miso_expand_quotes(t_shell *miso, t_token *node, char *str)
{
	char	*res;
	return (0);
}

char	*miso_expand(t_shell *miso, char *str)
{
	char	*res;
	int		i;

	res = miso_allocate_str(miso, 1);
	i = 0;
	while (str[i])
	{
		if (str[i] == '$' && str[i + 1] == '?')
			res = miso_exp_exit_code(miso, res, &i);
		else if (str[i] == '$' && str[i + 1] != '?')
			res = miso_exp_env(miso, res, &str[i], &i);
		else//NOTE: make this while loop?
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
		exp = miso_str_to_str(miso, res, exp_part);
	}
	free(exp_name);
	return (exp);
}
