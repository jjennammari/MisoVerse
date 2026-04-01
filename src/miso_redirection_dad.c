/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miso_redirection_dad.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-san- <lde-san-@student.42porto.co      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/28 19:17:12 by lde-san-          #+#    #+#             */
/*   Updated: 2026/04/01 19:51:42 by lde-san-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/miso.h"

int			miso_set_channel_dad(t_token *head);
static int	miso_scan_redin(t_token *head, int *fd);
static int	miso_scan_redout(t_token *lst, int *fd);

int	miso_set_channel_dad(t_token *head)
{
	int	tmp_fd;
	int	file_exit;

	tmp_fd = 0;
	file_exit = miso_scan_redin(head, &tmp_fd);
	if (file_exit)
		return (file_exit);
	if (tmp_fd)
	{
		dup2(tmp_fd, 0);
		close(tmp_fd);
	}
	tmp_fd = 0;
	file_exit = miso_scan_redout(head, &tmp_fd);
	if (file_exit)
		return (file_exit);
	if (tmp_fd)
	{
		dup2(tmp_fd, 1);
		close(tmp_fd);
	}
	return (0);
}
/* Are there are pipes in the line? Are there redirections? it will
validate these scenarios, set the corresponding fds, and close all
unecessary ones in order to set the "channel" that the data will go
through in order to excecute the command. It assumes that the read
and write end of the pipe won't be needed after the call. */

static int	miso_scan_redin(t_token *head, int *fd)
{
	while (head && head->type != PIPE)
	{
		if (head->type == RD_IN)
		{
			if (*fd != 0)
				close(*fd);
			if (!head->next->str)
				*fd = -1;
			else
				*fd = open(head->next->str, O_RDONLY);
			if (*fd == -1)
			{
				write(2, ORNG, ft_strlen(ORNG));
				write(2, head->next->str, ft_strlen(head->next->str));
				perror(RSET": "BLOD PROMPT RSET);
				return (1);
			}
		}
		head = head->next;
	}
	return (0);
}
/*Scans the line segment for input redirections, if it finds any, it returns
the file descriptor it stores in the *fd buffer passed */

static int	miso_scan_redout(t_token *lst, int *fd)
{
	while (lst && lst->type != PIPE)
	{
		if (lst->type == RD_OUT || lst->type == APPEND)
		{
			if (*fd != 0)
				close(*fd);
			if (!lst->next->str)
				*fd = -1;
			if (lst->type == RD_OUT && lst->next->str)
				*fd = open(lst->next->str, O_WRONLY | O_CREAT | O_TRUNC, 0644);
			else if (lst->type == APPEND && lst->next->str)
				*fd = open(lst->next->str, O_WRONLY | O_CREAT | O_APPEND, 0644);
			if (*fd == -1)
			{
				write(2, ORNG, ft_strlen(ORNG));
				write(2, lst->next->str, ft_strlen(lst->next->str));
				return (perror(RSET": "BLOD PROMPT RSET), 1);
			}
		}
		lst = lst->next;
	}
	return (0);
}
/*Scans the line segment for output redirections, if it finds any, it returns
the file descriptor it stores in the *fd buffer passed */
