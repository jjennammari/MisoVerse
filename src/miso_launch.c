/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miso_launch.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-san- <lde-san-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/21 18:28:07 by lde-san-          #+#    #+#             */
/*   Updated: 2026/03/31 23:23:03 by lde-san-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/miso.h"

int				miso_launch(t_shell *miso, t_token *head);
static int		miso_single_exec(t_shell *miso, char **cmd);
static pid_t	miso_multi_exec(t_shell *miso, t_token *head, int p_num);
static int		miso_rn(t_shell *miso, t_token *head);

int	miso_launch(t_shell *miso, t_token *head)
{
	int		seg_num;
	int		exit_status;
	pid_t	last_child;

	miso_setup_running_signals();
	if (!head)
		return (miso->exit_code);
	exit_status = 0;
	seg_num = miso_seg_count(head);
	if (seg_num > 1)
		last_child = miso_multi_exec(miso, head, seg_num);
	else
		return (miso_rn(miso, head));
	return (miso_waitroom(last_child, &exit_status));
}
/* Counts the number of command segments to call the corresponding execution
function. If necessary, it waitpid()s for the PID the miso_multiexec function
returns. To hold on to the exit status of the last child, and processing it,
to return the last exit code once all processes have ended. */

static int	miso_rn(t_shell *miso, t_token *head)
{
	char	**cmd;
	int		exit_code;
	int		std_cpy[2];

	cmd = NULL;
	std_cpy[0] = dup(0);
	std_cpy[1] = dup(1);
	if (std_cpy[0] == -1 || std_cpy[1] == -1)
		return (perror(BLOD PROMPT RSET), 1);
	exit_code = miso_set_channel_dad(head);
	if (exit_code == 0 && !miso_no_comands(head))
	{
		exit_code = miso_argv(miso, head, &cmd);
		if (exit_code == 0)
			exit_code = miso_single_exec(miso, cmd);
	}
	dup2(std_cpy[0], 0);
	dup2(std_cpy[1], 1);
	close(std_cpy[0]);
	close(std_cpy[1]);
	if (cmd)
		miso_free_matrix(cmd);
	return (exit_code);
}

static int	miso_single_exec(t_shell *miso, char **cmd)
{
	int		(*built_in)(t_shell *, char **);
	pid_t	child;
	int		exit_status;

	child = 0;
	built_in = miso_get_builtin(cmd[0]);
	if (!built_in)
	{
		child = fork();
		if (child == 0)
		{
			miso_setup_child_signals();
			miso_call_program(miso, cmd);
			return (127);
		}
		return (miso_waitroom(child, &exit_status));
	}
	return (built_in(miso, cmd));
}

static pid_t	miso_multi_exec(t_shell *miso, t_token *head, int p_num)
{
	int		p[2];
	pid_t	last_child;
	int		prev_read;

	prev_read = -1;
	last_child = 0;
	while (p_num)
	{
		if (p_num - 1 != 0)
			pipe(p);
		last_child = fork();
		if (last_child == 0)
		{
			miso_setup_child_signals();
			if (miso_no_comands(head))
				misoverse_free_exit(miso, 0, miso_just_redirect(head));
			if (p_num - 1 != 0)
				miso_channeling(miso, prev_read, p, p_num);
			else
				miso_channeling(miso, prev_read, NULL, p_num);
			miso_get_argv_nrun(miso, head);
		}
		head = miso_next_segment(head);
		miso_daddy_pipe_manager(&prev_read, p, p_num);
		p_num--;
	}
	return (last_child);
}
/* If there are pipes, it will iterate through each segment creating
pipes, fork()-ing the corresponding child processes and eventually 
calling execve with the passed command. The function then holds on to
the PID of the last child, and returns it.  */
