/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miso_launch.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-san- <lde-san-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/21 18:28:07 by lde-san-          #+#    #+#             */
/*   Updated: 2026/03/08 22:27:12 by lde-san-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/miso.h"

int				miso_launch(t_shell *miso, t_token *head);
static int		miso_single_exec(t_shell *miso, t_token *head);
static pid_t	miso_multi_exec(t_shell *miso, t_token *head, int p_num);

int	miso_launch(t_shell *miso, t_token *head)
{
	int		seg_num;
	int		exit_status;
	pid_t	last_child;

	seg_num = 0;
	exit_status = 0;
	seg_num = miso_seg_count(head);
	if (seg_num > 1)
		last_child = miso_multi_exec(miso, head, seg_num);
	else
		return (miso_single_exec(miso, head));
	return (miso_waitroom(last_child, &exit_status));
}
/* Counts the number of command segments to call the corresponding execution
function. If necessary, it waitpid()s for the PID the miso_multiexec function
returns. To hold on to the exit status of the last child, and processing it,
to return the last exit code once all processes have ended. */

static int	miso_single_exec(t_shell *miso, t_token *head)
{
	pid_t	child;
	char	**cmd;
	int		exit_code;
	int		(*built_in)(t_shell *, char **);

	child = 0;
	exit_code = 127;
	cmd = miso_argv(head, miso->envp);
	built_in = miso_get_builtin(cmd[0]);
	if (!built_in)
	{
		child = fork();
		if (child == 0)
		{
			miso_setup_child_signals();
			miso_channeling(0, head, NULL, -1);
			miso_call_program(miso, cmd, head);
		}
	}
	else
		exit_code = miso_rn(miso, cmd, head, built_in);
	if (child > 0)
		return (miso_waitroom(child, &exit_code));
	return (exit_code);
}
/* It executes a singular command segment, ensuring that child processes
are created only when estrictly necessary. It returns the PID of the child
it created, or 0 if it called a built-in.*/

static pid_t	miso_multi_exec(t_shell *miso, t_token *head, int p_num)
{
	int		p[2];
	pid_t	last_child;
	int		prev_read;

	prev_read = -1;
	last_child = 0;
	while (p_num)
	{
		if (!head)
			racc_print(2, BLOD"PROMPT"MINT" Unexpected Syntax"RSET);
		if (p_num - 1 != 0)
			pipe(p);
		last_child = fork();
		if (last_child == 0)
		{
			miso_setup_child_signals();
			miso_channeling(prev_read, head, p, p_num);
			miso_call_program(miso, miso_argv(head, miso->envp), head);
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
