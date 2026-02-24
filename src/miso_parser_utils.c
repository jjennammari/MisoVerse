/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miso_parser_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jemustaj <jemustaj@student.42Porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/13 12:44:36 by jemustaj          #+#    #+#             */
/*   Updated: 2026/02/24 15:12:14 by jemustaj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/parsing.h"

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

void	set_commandtype(t_shell *miso, t_token *node)
{
	if (is_builtin(node->str))
		miso->node->type = BLT_CMD;
	else
		miso->node->type = SYS_CMD;
}
