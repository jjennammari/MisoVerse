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

#include "../inc/miso.h"

int	miso_is_builtin(char *word)
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

void	miso_set_commandtype(t_shell *miso, t_token *node)
{
	if (miso_is_builtin(node->str))
		miso->node->type = BLT_CMD;
	else
		miso->node->type = SYS_CMD;
}

void	miso_search_cmd(t_shell *miso, t_token *node)
{
	if (node->type == ARG)
	{
		miso_set_commandtype(miso, node);
		miso->list.cmd_found = 1;
	}
}

int	miso_is_redirection(t_token_type type)
{
	if (type == RD_IN || type == RD_OUT || type == APPEND || type == HEREDOC)
		return (1);
	return (0);
}
