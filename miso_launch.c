/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miso_launch.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-san- <lde-san-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/21 18:28:07 by lde-san-          #+#    #+#             */
/*   Updated: 2026/01/27 00:28:22 by lde-san-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miso.h"

int	miso_launch(t_miso *shell, t_token *head)
{
	int		seg_num;
	int		exit_status;
	pid_t	last_child;

	seg_num = 0;
	exit_status = 0;
	seg_num = miso_seg_count(head);
	if (seg_num > 1)
		last_child = miso_multiexec(shell, head, seg_num);
	else
		return(miso_exec(shell, head));
	return(miso_waitroom(last_child, &exit_status));
}
/* Counts the number of command segments to call the corresponding execution
function. If necessary, it waitpid()s for the PID the miso_multiexec function
returns. To hold on to the exit status of the last child, and processing it,
to return the last exit code once all processes have ended. */

int	miso_waitroom(pid_t child, int *exit_status)
{
	waitpid(child, exit_status, 0);
	while (wait(NULL) > 0)
		continue ;
	if (WIFEXITED(*exit_status))
		return(WEXITSTATUS(*exit_status));
	else if (WIFSIGNALED(*exit_status))
		return(128 + WTERMSIG(*exit_status));
	return(0);
}
/* Waits for the passed process ID to finish, in order to translate the 
exit status into the exit code that will be returned. While the proyect
doesn't ask to handle other stop reasons like WIFCONTINUED or WIFSTOPPED,
they are a posibility. That posibility, we've decided to handle as a successful
end, so the function will return 0 by default.*/

int	miso_exec(t_miso *shell, t_token *head)
{
	pid_t	child;
	char	**cmd;
	int		std_cpy[2];
	int		exit_code;

	child = 0;
	exit_code = 127;
	cmd = miso_argv(head);
	if (!miso_is_builtin(cmd[0]))
	{
		child = fork();
		if (child == 0)
		{
			miso_channeling(0, head, NULL, -1);
			miso_call_program(shell, cmd, shell->envp);
			perror(BLOD"PROMPT"RSET);
			miso_free_matrix(cmd);
			exit(exit_code);
		}
	}
	else
	{
		std_cpy[0] = dup(0);
		std_cpy[1] = dup(1);
		miso_channeling(0, head, NULL, -1);
		exit_code = miso_call_builtin(shell, cmd); // Pending, check how they'd be called;
		dup2(std_cpy[0], 0);
		dup2(std_cpy[1], 1);
		close(std_cpy[0]);
		close(std_cpy[1]);
	}
	if (child > 0)
		return (miso_waitroom(child, &exit_code));
	return (exit_code);
}
/* It executes a singular command segment, ensuring that child processes
are created only when estrictly necessary. It returns the PID of the child
it created, or 0 if it called a built-in.*/

void	miso_channeling(int prev_read, t_token *head, int *p, int p_num)
{
	if(p_num == -1)
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

int	miso_is_builtin(char *cmd)
{
	size_t	len;

	len = ft_strlen(cmd);
	if (!ft_strncmp("echo", cmd, len) && (len == 4))
		return (1);
	if (!ft_strncmp("cd", cmd, len) && (len == 2))
		return (1);
	if (!ft_strncmp("pwd", cmd, len) && (len == 3))
		return (1);
	if (!ft_strncmp("export", cmd, len) && (len == 6))
		return (1);
	if (!ft_strncmp("unset", cmd, len) && (len == 5))
		return (1);
	if (!ft_strncmp("env", cmd, len) && (len == 3))
		return (1);
	if (!ft_strncmp("exit", cmd, len) && (len == 4))
		return (1);
	return (0);
}
/* Uses ft_strncmp and the lenght of the incoming string "cmd" to analyze
if the command being called is one of the built-in functions */

void	miso_call_program(t_miso *shell, char **cmd, char **envp)
{
	int	exit_code;

	exit_code = 127;
	if (miso_is_builtin(cmd[0]))
		exit_code = miso_call_builtin(shell, cmd); // Pending, check how they'd be called;
	else
		execve(cmd[0], cmd + 1, envp);
	if (exit_code == 0)
		exit(0);
	perror(BLOD"PROMPT"RSET);
	miso_free_matrix(cmd);
	exit(exit_code);
}
/* Determines whether the comand will be executed with execve or
ran with a built-in function. In either case it is expected for
the "execution" to take over and exit accordingly, therefore, if
the function reaches the perror line, it assumes that an error
ocurred, and the function exits accordingly. */

void	miso_daddy_pipe_manager(int *prev_read, int *p, int p_num)
{
	if (*prev_read != -1)
		close(*prev_read);
	if (p_num - 1 != 0)
	{
		close(p[1]);
		*prev_read = p[0];
	}
	return ;
}
/* Updates the prev_read variable with the read end of the last pipe
created, and closes the last write end since is no longer needed in
the parent process */

pid_t	miso_multiexec(t_miso *shell, t_token *head, int p_num)
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
			miso_channeling(prev_read, head, p, p_num);
			miso_call_program(shell, miso_argv(head), shell->envp);
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
the PID of the las child, and returns it.  */

void	miso_redir(int new_fd, int def_fd)
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

int	miso_scan_redin(t_token *head, int *fd)
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

int	miso_scan_redout(t_token *lst, int *fd)
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

void	miso_set_channel(t_token *head, int in, int out, int *pipe)
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

char	**miso_argv(t_token *head)
{
	t_token	*trav;
	int		argc;
	char	*argv;

	trav = head;
	argc = 1;
	while (trav && trav->type != CMD && trav->type != BLTIN)
		trav = trav->next;
	if (trav->type != BLTIN)
		miso_pathfinder(&trav->str);
	while (trav && trav->type != PIPE)
	{
		if (trav->type == ARG)
			argc++;
		trav = trav->next;
	}
	argv = ft_calloc(argc + 1, sizeof(char *));
	miso_checknfree(NULL, argv, NULL, NULL);
	return (miso_populate(argv, argc, head));
}
/*Advances until it finds the comand, and if is not a built-in, or has
a literal path, it updates the str* with the path to the program. Then it 
counts the arguments passed in order to allocate the argv 2D array and 
populate it with the strings from the list. */

char	**miso_populate(char **argv, int argc, t_token *head)
{
	t_token	*trav;
	int		guide;

	argv[argc] = NULL;
	trav = head;
	guide = 0;
	while (guide < argc && trav && trav->type != PIPE)
	{
		if (trav->type == CMD || trav->type == BLTIN || trav->type == ARG)
		{
			argv[guide] = trav->str;
			guide++;
		}
		trav = trav->next;
	}
	return (argv);
}
/* It traverses through the list as it iterates through the passed
argv buffer, in order to set in order the commands and its arguments.
Essentially creating the argument vector that will be passed to 
execve(). It assumes that there is only one comand of either type CMD
or BLTIN, and that the conditions are optimally configured so all 
arguments come after the comand. */

void	miso_pathfinder(char **cmd)
{
	char	**dirs;
	int		guide;
	char	*path_name;
	char	*temp;
	char	*old_str;

	if (ft_strchr(*cmd, '/'))
		return ;
	dirs = ft_split(getenv("PATH"), ':');
	miso_checknfree(NULL, dirs, NULL, NULL);
	temp = ft_strjoin("/", *cmd);
	miso_checknfree(temp, NULL, NULL, dirs);
	path_name = miso_pathmatch(dirs, temp);
	miso_checknfree(path_name, NULL, temp, dirs);
	free(temp);
	miso_free_matrix(dirs);
	miso_customs(path_name, access(path_name, F_OK));
	old_str = *cmd;
	*cmd = path_name;
	free(old_str);
	return ;
}
/*It splits the directories coming from the PATH variable, in order to
create a strig that will contain the full path to the command passed. 
It will return early if the file contains a "/", as it would indicate
that its being called with a literal path. The path is pre-validated
to ensure that the correct error code and message gets sent. It frees
the memory of the previous string stored in the node, replacing it 
with the newly found path. It assumes that the command passed is not 
built-in*/

void	miso_customs(char *program, int doesnt_exist)
{
	t_stat	metadata;

	if (doesnt_exist)
	{
		perror(BLOD"PROMPT"RSET);
		free(program);
		exit(1);
	}
	if (stat(program, &metadata) == -1)
	{
		perror(BLOD"PROMPT"RSET);
		free(program);
		exit(127);
	}
	else if (S_ISDIR(metadata.st_mode))
	{
		racc_print(2, BLOD"PROMPT: "MINT"%s"RSET": Is a directory\n", program);
		exit(126);
	}
	return ;
}
/* It checks the metadata found by stat, to check if the path goes to a
program or a directory, in order to print the correct error message and
exit accordingly. The function is meant to be called with with the 
access() function on the second parameter, to validate if the "object"
doesn't exist. */

char	*miso_pathmatch(char **dirs, char *temp_filename)
{
	int		guide;
	char	*path_name;

	if (!temp_filename || !dirs)
		return (NULL);
	guide = 0;
	path_name = ft_strjoin(dirs[guide], temp_filename);
	if (!path_name)
		return (NULL);
	while (access(path_name, F_OK) && dirs[guide])
	{
		guide++;
		if (!dirs[guide])
			break ;
		free(path_name);
		path_name = ft_strjoin(dirs[guide], temp_filename);
		if (!path_name)
			return (NULL);
	}
	return (path_name);
}
/* Iterates through all the provided directories, checking if the file
passed exists. It will return the full path to the program or NULL if 
it doesn't find it, assuming that the command passed is not built-in */

void	miso_checknfree(void *check1, void **check2, void *free1, void **free2)
{
	if (check1 || check2)
		return ;
	perror(BLOD"PROMPT"RSET);
	if (free1)
		free(free1);
	if (free2)
		miso_free_matrix(free2);
	exit(66);
}
/* Mainly for checking memory allocations, this option takes either a * or
** pointer to check and one to free previous dependencies if necessary. The
function will print the message from errno if necessary and exit with a 
common error code */

void	miso_free_matrix(char **matrix)
{
	int	guide;

	if (!matrix)
		return ;
	guide = 0;
	while (matrix[guide])
	{
		free(matrix[guide]);
		guide++;
	}
	free(matrix);
	return ;
}
/*Traverses all the pointers in the 2D array passed, freeing its contents and
eventually the array itself. It assumes that all pointers in the array either
are allocated or NULL, and that the array has a NULL pointer only at the end.*/

int	miso_seg_count(t_token *head)
{
	int		guide;
	t_token	*trav;

	trav = head;
	guide = 0;
	while (trav)
	{
		if (trav->type == PIPE)
			guide++;
		trav = trav->next;
	}
	if (!guide)
		return (1);
	return (guide + 1);
}
/*Traverses the list looking for pipes, in order to return the number of
segments in the line. By default it returns one as it assumes that the 
input will never be an empty line.*/
