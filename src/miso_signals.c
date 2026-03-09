/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miso_signals.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-san- <lde-san-@student.42porto.co      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/05 18:19:36 by lde-san-          #+#    #+#             */
/*   Updated: 2026/03/09 20:01:30 by lde-san-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/miso.h"

void    miso_fdshutdown(void);
void    miso_daddy_sigint(int sig);
void    miso_init_daddy_signals(void);
void    miso_setup_child_signals(void);

void	miso_daddy_sigint(int sig)
{
	g_signal = sig;
	write(1, "\n", 1);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
	miso_fdshutdown();
	return ;
}
/* Handles SIGINT for the parent process. Resetting readline, printing
a newline, and setting the global signal accordingly. */


void	miso_fdshutdown(void)
{
	int fd;

	fd = 3;
	while (fd <= 1024)
		close(fd++);
	return ;
}

void	miso_init_daddy_signals(void)
{
	t_sigact	miso_sigint;
	t_sigact	miso_sigquit;

	ft_memset(&miso_sigint, 0, sizeof(miso_sigint));
	ft_memset(&miso_sigint, 0, sizeof(miso_sigquit));
	miso_sigint.sa_handler = miso_daddy_sigint;
	miso_sigquit.sa_handler = SIG_IGN;
	miso_sigint.sa_flags = SA_RESTART;
	miso_sigquit.sa_flags = 0;
	sigemptyset(&miso_sigint.sa_mask);
	sigemptyset(&miso_sigquit.sa_mask);
	sigaction(SIGINT, &miso_sigint, NULL);
	sigaction(SIGQUIT, &miso_sigquit, NULL);
	return ;
}

void	miso_setup_child_signals(void)
{
	t_sigact	miso_child_sigint;

	ft_memset(&miso_child_sigint, 0, sizeof(miso_child_sigint));
	miso_child_sigint.sa_handler = SIG_DFL;
	miso_child_sigint.sa_flags = 0;
	sigemptyset(&miso_child_sigint.sa_mask);
	sigaction(SIGINT, &miso_child_sigint, NULL);
	return ;
}
