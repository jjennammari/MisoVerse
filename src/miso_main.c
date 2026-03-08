/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miso_main.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jemustaj <jemustaj@student.42Porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/29 22:47:52 by jemustaj          #+#    #+#             */
/*   Updated: 2026/03/08 22:31:42 by lde-san-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/miso.h"

int	main(int argc, char **argv, char **envp)
{
	t_shell	miso;

	(void)argc;
	(void)argv;
	miso_init_variables(&miso, envp);
	misoverse_loop(&miso);
	return (1);
}

void	miso_init_variables(t_shell *miso, char **envp)
{
	miso->exit_code = 0;
	miso->envp = miso_envinit(envp);
	miso_exp_innit(miso, *envp);
	miso->list.cmd_found = 0;
	miso->list.head = NULL;
	miso->list.hd_count = 0;
	miso->list.last_node = NULL;
	miso->node = malloc(sizeof(t_token));
	if (!miso->node)
	{
		misoverse_free(miso, 1);
		exit(1);
	}
	miso->node->expand = 0;
	miso->node->str = NULL;
	miso->node->next = NULL;
	miso->node->is_quotet = 0;
	return ;
}
