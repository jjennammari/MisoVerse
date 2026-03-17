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

void	miso_expand_quotes(t_shell *miso, t_token *node);
char	*miso_exp_with_quotes(t_shell *miso, t_token *node, char *str);
void	miso_validate_expansion(t_shell *miso, t_token *node, char c, int *pi);
void	miso_update_quotes(t_shell *miso, char c);

void	miso_expand_quotes(t_shell *miso, t_token *node)
{
	char	*res;

	res = miso_exp_with_quotes(miso, node, node->str);
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
			miso_validate_expansion(miso, node, str[i], NULL);
		if (str[i] == '$' && node->expand == 1)
		{
			if (str[i + 1] == '?')
				res = miso_exp_exit_code(miso, res, &i);
			else
				res = miso_exp_env(miso, res, &str[i], &i);
			continue ;
		}
		res = miso_add_char_str(miso, res, str[i]);
		i++;
	}
	return (res);
}

void	miso_validate_expansion(t_shell *miso, t_token *node, char c, int *pi)
{
	if (c == '\'' && miso->list.dquote == 0)
	{
		node->expand = 0;
		miso_update_quotes(miso, c);
		if (miso->list.squote == 0)
			node->expand = 1;
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
	if (pi)
		*pi += 1;
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
