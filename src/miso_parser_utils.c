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
	if (!ft_strncmp("echo", word, 5))
		return (1);
	else if (!ft_strncmp("cd", word, 3))
		return (1);
	if (!ft_strncmp("pwd", word, 4))
		return (1);
	if (!ft_strncmp("export", word, 7))
		return (1);
	if (!ft_strncmp("unset", word, 6))
		return (1);
	if (!ft_strncmp("env", word, 4))
		return (1);
	if (!ft_strncmp("exit", word, 5))
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
