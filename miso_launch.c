/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miso_launch.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-san- <lde-san-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/21 18:28:07 by lde-san-          #+#    #+#             */
/*   Updated: 2026/01/25 13:34:18 by lde-san-         ###   ########.fr       */
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
		last_child = miso_multiexec(miso, head, seg_num);
	else
		last_child = miso_exec(miso, head);
}
/*Counts the number of command segments to call the corresponding execution
function. Then waitpid()s for the value they return to hold to the exit 
status, processing it to update the last exit code, and returning it once
all processes have ended.*/

pid_t miso_exec(t_token *head);
{

}
/*It executes a singular command segment, ensuring that child processes
are created only when estrictly necessary. It returns the PID of the child
it created, or 0 if it called a built-in.*/

pid_t miso_multiexec(t_token *head, int p_num)
{
	char	**cmd;
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
			if (prev_read == -1)
				miso_set_channel(head, 0, p[1], &p);
			else
			{
				if (p_num - 1 == 0)
					miso_set_channel(head, prev_read, 1, &p);
				else
					miso_set_channel(head, prev_read, p[1], &p);
			}
		}
		p_num--;
	}
}
/* If there are pipes, it will iterate through each segment creating
pipes, fork()-ing the corresponding child processes and eventually 
calling execve with the passed command. The function then holds on to
the PID of the las child, and returns it.  */

void miso_set_channel(t_token *head, int in, int out, int **pipe)
{
	int     fdin;
	int     fdout;

	fdin = 0;
	fdout = 1;
	close(pipe[0]);
	if (!miso_redirin(head, in, &fdin))
	{
		if (in != 0)
		{
			dup2(in, 0);
			close(in);
		}
	}
	else
	{
		dup2(fdin, 0);
		close(out);
	}
	if (!miso_redirout(head, out, &fdout))
	{
		if (out != 1)
		{
			dup2(out, 1)
			close(out)
		}
	}
	else
	{
		dup2(fdin, 0);
		close(out);
	}
}
/* If there are pipes in the line, it will check for redirections and 
open the files accordingly to set the fds to its corresponding values
and dup2() them with the pipe, to set the "channel" that the data will
go through in order to excecute the command */

char **miso_argv(t_token *head)
{
	t_token *trav;
	int		argc;
	char	*argv;

	trav = head;
	argc = 1;
	while(trav && trav->type != CMD && trav->type != BLTIN)
		trav = trav->next;
	if (trav->type != BLTIN)
		miso_pathfinder(trav->str);
	while(trav && trav->type != PIPE)
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
	t_token *trav;
	int		guide;

	argv[argc] = NULL;
	trav = head;
	guide = 0;
	while(guide < argc && trav && trav->type != PIPE)
	{
		if (trav->type == CMD || trav->type == BLTIN || trav->type == ARG)
		{
			argv[guide] = trav->str;
			guide++;
		}
		trav = trav->next;
	}
	return(argv);
}
/* It traverses through the list as it iterates through the passed
argv buffer, in order to set in order the commands and its arguments.
Essentially creating the argument vector that will be passed to 
execve(). It assumes that there is only one comand of either type CMD
or BLTIN, and that the conditions are optimally configured so all 
arguments come after the comand. */

void miso_pathfinder(char *cmd)
{
	char	**dirs;
	int		guide;
	char	*path_name;
	char	*temp;
	char	*old_str;

	if (ft_strchr(cmd_in, '/'))
		return ;
	dirs = ft_split(getenv("PATH"), ':');
	miso_checknfree(NULL, dirs, NULL, NULL);
	temp = ft_strjoin("/", cmd);
	miso_checknfree(temp, NULL, NULL, dirs);
	path_name = miso_pathmatch(dirs, temp);
	miso_checknfree(path_name, NULL, temp, dirs);
	free(temp);
	miso_free_matrix(dirs);
	miso_customs(path_name, access(path_name, F_OK));
	old_str = cmd;
	cmd = path_name;
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

void miso_customs(char *program, int exists)
{
	t_stat	metadata;

	if (exists)
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
	else if (S_ISDIR(&metadata.st_mode))
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
exists */

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

void miso_checknfree(void *check1, void **check2, void *free1, void **free2)
{
	if (check1 || check2)
		return ;
	perror(BLOD"PROMPT"RSET);
	if (free1)
		free(free1);
	if (free2)
		miso_free_matrix(free2);
	exit(1);
}
/* Mainly for chacking memory allocations, this option takes either a * or
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

int miso_seg_count(t_token *head);
{
	int		guide;
	t_token	*trav;

	trav = head;
	guide = 0;

	while(trav)
	{
		if(trav->type == PIPE)
			guide++;
		trav = trav->next;
	}
	if (!guide)
		return (1);
	return(guide + 1);
}
/*Traverses the list looking for pipes, in order to return the number of
segments in the line. By default it returns one as it assumes that the 
input will never be an empty line.*/
