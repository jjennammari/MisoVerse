/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miso_tokenization_utils.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jemustaj <jemustaj@student.42Porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/29 22:48:35 by jemustaj          #+#    #+#             */
/*   Updated: 2026/02/13 13:45:38 by jemustaj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	is_whitespace(char c)
{
	if (c == 32 || c >= 9 & c <= 13)
		return (1);
	return (0);
}

int	is_squote(char c)
{
	if (c == '\'')
		return (1);
	return (0);
}

int	is_dquote(char c)
{
	if (c == '"')
		return (1);
	return (0);
}

int	is_builtin(char *word)
{
	if (ft_strcmp("echo", word))
		return (1);
	else if (ft_strcmp("cd", word))
		return (1);
	if (ft_strcmp("pwd", word))
		return (1);
	if (ft_strcmp("export", word))
		return (1);
	if (ft_strcmp("unset", word))
		return (1);
	if (ft_strcmp("env", word))
		return (1);
	if (ft_strcmp("exit", word))
		return (1);
	return (0);
}

void	set_commandtype(t_token *node)
{
	if (is_builtin(node->str))
		node->type = BLT_CMD;
	else
		node->type = SYS_CMD;
}
