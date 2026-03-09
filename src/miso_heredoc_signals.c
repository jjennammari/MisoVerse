/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miso_heredoc_signals.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jemustaj <jemustaj@student.42Porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/08 22:52:20 by jemustaj          #+#    #+#             */
/*   Updated: 2026/03/08 23:36:33 by jemustaj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/miso.h"

static void	miso_hd_sigint(int sig);

int	miso_hd_handle_signals(struct sigaction *old_int, struct sigaction *old_quit)
{
	t_sigact	act;

	g_signal = 0;
	ft_bzero(&act, sizeof(act));
	act.sa_handler = miso_hd_sigint;
	sigemptyset(&act.sa_mask);
	if (sigaction(SIGINT, &act, old_int) == -1)
		return (1);
	act.sa_handler = SIG_IGN;
	if (sigaction(SIGQUIT, &act, old_quit) == -1)
		return (sigaction(SIGINT, old_int, NULL), 1);
	return (0);
}

static void	miso_hd_sigint(int sig)
{
	g_signal = sig;
	write(1, "\n", 1);
}

int	miso_hd_restore_signals(struct sigaction *old_int, struct sigaction *old_quit)
{
	if (sigaction(SIGINT, old_int, NULL) == -1)
		return (1);
	if (sigaction(SIGQUIT, old_quit, NULL) == -1)
		return (1);
	return (0);
}
