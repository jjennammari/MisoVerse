/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miso_main.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jemustaj <jemustaj@student.42Porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/29 22:47:52 by jemustaj          #+#    #+#             */
/*   Updated: 2026/02/20 20:48:05 by jemustaj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/miso.h"

int	main(int argc, char **argv, char **envp)
{
	t_shell	miso;

	miso_init_variables(&miso, argc, argv);
	misoverse_loop(&miso);
	misoverse_free(&miso);
	return (0);
}

void	miso_init_variables(t_shell *miso, int argc, char **argv)
{
	(void)argc;
	(void)argv;
	miso->exit_code = 0;
	miso->node = malloc(sizeof(t_token));
	if (!miso->node)
		return ;
	miso->node->expand = 0;
	miso->node->str = NULL;
	miso->node->next = NULL;
	miso->node->hd.is_quotet = 0;
	miso->node->hd.delim = NULL;
	miso->list.cmd_found = 0;
	miso->list.head = NULL;
	miso->list.last_node = NULL;
}
