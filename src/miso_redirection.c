/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miso_redirection.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-san- <lde-san-@student.42porto.co      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/28 19:17:12 by lde-san-          #+#    #+#             */
/*   Updated: 2026/02/02 19:06:45 by lde-san-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/miso.h"

static void	miso_redir(int new_fd, int def_fd);
static int	miso_scan_redin(t_token *head, int *fd);
static int	miso_scan_redout(t_token *lst, int *fd);
static void	miso_set_channel(t_token *head, int in, int out, int *pipe);
void		miso_channeling(int prev_read, t_token *head, int *p, int p_num);

static void	miso_redir(int new_fd, int def_fd)
{
	if (new_fd != def_fd)
	{
		dup2(new_fd, def_fd);
		close(new_fd);
	}
	return ;
}
/* If the new fd that's being set up, is not the default one,
it will dup2()-it in order to redirect the data to or from the
correct place. Closing the new_fd in the process in order to
avoid leaks. It assumes that new_fd will no longer be needed
after this call*/

void	miso_channeling(int prev_read, t_token *head, int *p, int p_num)
{
	if (p_num == -1)
	{
		miso_set_channel(head, 0, 1, NULL);
		return ;
	}
	if (prev_read == -1)
		miso_set_channel(head, 0, p[1], p);
	else
	{
		if (p_num - 1 == 0)
			miso_set_channel(head, prev_read, 1, p);
		else
			miso_set_channel(head, prev_read, p[1], NULL);
	}
	return ;
}
/* It ensures tha the correct input and output stream is being sent to the
set_channel evaluation, corresponding to which stage of the loop the function
gets called. It's based on three basic stages, the begining of the line,
the middle sections, and the end. If if is called at the end, it sends NULL
instead of the pipe, because the function assumes no further pipes were 
created. The p_num == -1 case, is for the special condition of there being
only one segment and no pipes. */

static void	miso_set_channel(t_token *head, int in, int out, int *pipe)
{
	int	tmp_fd;

	tmp_fd = 0;
	if (pipe)
		close(pipe[0]);
	if (!miso_scan_redin(head, &tmp_fd))
		miso_redir(in, 0);
	else
	{
		miso_redir(tmp_fd, 0);
		close(in);
	}
	tmp_fd = 0;
	if (!miso_scan_redout(head, &tmp_fd))
		miso_redir(out, 1);
	else
	{
		miso_redir(tmp_fd, 1);
		close(out);
	}
	if (pipe)
		close(pipe[1]);
	return ;
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
			if (!head->next)
			{
				racc_print(2, BLOD"PROMPT"MINT"Error after `%s'\n", head->str);
				exit(2);
			}
			*fd = open(head->next->str, O_RDONLY);
			if (*fd == -1)
			{
				perror(BLOD"PROMPT"RSET);
				exit(126);
			}
		}
		head = head->next;
	}
	return (*fd);
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
			if (!lst->next)
			{
				racc_print(2, BLOD"PROMPT"MINT"Error after `%s'\n", lst->str);
				exit(2);
			}
			if (lst->type == RD_OUT)
				*fd = open(lst->next->str, O_WRONLY | O_CREAT | O_TRUNC, 0644);
			else if (lst->type == APPEND)
				*fd = open(lst->next->str, O_WRONLY | O_CREAT | O_APPEND, 0644);
			if (*fd == -1)
			{
				perror(BLOD"PROMPT"RSET);
				exit(126);
			}
		}
		lst = lst->next;
	}
	return (*fd);
}
/*Scans the line segment for output redirections, if it finds any, it returns
the file descriptor it stores in the *fd buffer passed */
