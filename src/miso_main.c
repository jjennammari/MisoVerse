/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miso_main.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jemustaj <jemustaj@student.42Porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/29 22:47:52 by jemustaj          #+#    #+#             */
/*   Updated: 2026/03/17 21:57:18 by lde-san-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/miso.h"

int	g_signal = 0;

static void	miso_init_variables(t_shell *miso, char **envp);

int	main(int argc, char **argv, char **envp)
{
	t_shell	miso;

	(void)argc;
	(void)argv;
	miso_init_variables(&miso, envp);
	misoverse_loop(&miso);
	return (1);
}

static void	miso_init_variables(t_shell *miso, char **envp)
{
	miso->hd_files = 0;
	miso->exit_code = 0;
	miso->list.squote = 0;
	miso->list.dquote = 0;
	miso->list.cmd_found = 0;
	miso->list.hd_count = 0;
	miso->list.head = NULL;
	miso->list.last_node = NULL;
	miso->envp = NULL;
	miso->exp = NULL;
	miso->prompt = NULL;
	miso->envp = miso_envinit(miso, envp);
	miso_exp_innit(miso, *envp);
	miso->node = malloc(sizeof(t_token));
	if (!miso->node)
		misoverse_free_exit(miso, 1, 2);
	miso->node->expand = 0;
	miso->node->str = NULL;
	miso->node->next = NULL;
	miso->node->quotes = 0;
	return ;
}
