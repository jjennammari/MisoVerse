/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miso_handle_heredoc.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-san- <lde-san-@student.42porto.co      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/07 20:55:49 by lde-san-          #+#    #+#             */
/*   Updated: 2026/03/07 20:55:49 by lde-san-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/miso.h"

static void	miso_hd_setup(t_sigact *old);
static void	miso_hd_restore(t_sigact *old);
static void	miso_hd_child(int fd, char *delim);
static int	miso_hd_parent(t_shell *miso, t_token *node, char *tmp, int st);
int			miso_handle_heredoc(t_shell *miso, t_token *node);

static void	miso_hd_setup(t_sigact *old)
{
	t_sigact	sa;

	ft_memset(&sa, 0, sizeof(sa));
	sa.sa_handler = SIG_IGN;
	sigemptyset(&sa.sa_mask);
	sigaction(SIGINT, &sa, old);
}

static void	miso_hd_restore(t_sigact *old)
{
	sigaction(SIGINT, old, NULL);
}

static void	miso_hd_child(int fd, char *delim)
{
	t_sigact	sa;
	char		*line;

	ft_memset(&sa, 0, sizeof(sa));
	sa.sa_handler = SIG_DFL;
	sigemptyset(&sa.sa_mask);
	sigaction(SIGINT, &sa, NULL);
	line = readline("> ");
	while (line)
	{
		if (!ft_strncmp(line, delim, ft_strlen(delim) + 1))
		{
			free(line);
			close(fd);
			exit(0);
		}
		write(fd, line, ft_strlen(line));
		write(fd, "\n", 1);
		free(line);
		line = readline("> ");
	}
	write(2, "heredoc: EOF (wanted `", 22);
	write(2, delim, ft_strlen(delim));
	write(2, "')\n", 3);
	close(fd);
	exit(0);
}

static int	miso_hd_parent(t_shell *miso, t_token *node, char *tmp, int st)
{
	if (WIFSIGNALED(st) && WTERMSIG(st) == SIGINT)
	{
		miso->exit_code = 130;
		write(2, "\n", 1);
		unlink(tmp);
		free(tmp);
		return (1);
	}
	node->type = RD_IN;
	free(node->next->str);
	node->next->str = tmp;
	return (0);
}

int	miso_handle_heredoc(t_shell *miso, t_token *node)
{
	int			fd;
	char		*tmp;
	pid_t		pid;
	int			status;
	t_sigact	old_sa;

	tmp = miso_hd_tmpfile(&fd);
	if (!tmp || fd < 0)
		return (1);
	miso_hd_setup(&old_sa);
	pid = fork();
	if (pid < 0)
	{
		miso_hd_cleanup(fd, tmp);
		miso_hd_restore(&old_sa);
		return (1);
	}
	if (pid == 0)
		miso_hd_child(fd, node->next->str);
	close(fd);
	waitpid(pid, &status, 0);
	miso_hd_restore(&old_sa);
	return (miso_hd_parent(miso, node, tmp, status));
}
