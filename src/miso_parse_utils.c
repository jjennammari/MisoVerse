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

int	miso_is_builtin(char *arg)
{
	int	len;

	len = ft_strlen(arg);
	if (len == 2 && !ft_strncmp("cd", arg, len))
		return (1);
	if (len == 3 && !ft_strncmp("pwd", arg, len))
		return (1);
	if (len == 3 && !ft_strncmp("env", arg, len))
		return (1);
	if (len == 4 && !ft_strncmp("echo", arg, len))
		return (1);
	if (len == 4 && !ft_strncmp("exit", arg, len))
		return (1);
	if (len == 5 && !ft_strncmp("unset", arg, len))
		return (1);
	if (len == 6 && !ft_strncmp("export", arg, len))
		return (1);
	return (0);
}

void	miso_set_commandtype(t_token *node)
{
	if (miso_is_builtin(node->str))
		node->type = BLT_CMD;
	else
		node->type = SYS_CMD;
}

void	miso_search_cmd(t_shell *miso, t_token *node)
{
	if (node->type == ARG)
	{
		miso_set_commandtype(node);
		miso->list.cmd_found = 1;
	}
}

int	miso_is_redirection(t_token_type type)
{
	if (type == RD_IN || type == RD_OUT || type == APPEND || type == HEREDOC)
		return (1);
	return (0);
}
