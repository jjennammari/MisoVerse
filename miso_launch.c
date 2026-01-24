/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miso_launch.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-san- <lde-san-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/21 18:28:07 by lde-san-          #+#    #+#             */
/*   Updated: 2026/01/24 21:22:53 by lde-san-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miso.h"

int	miso_launch(t_miso *shell, t_token *head)
{
	int		seg_num;
	int		exit_status;

	seg_num = 0;
	exit_status = 0;
	seg_num = miso_seg_count(head);
	if (seg_num > 1)
		exit_status = miso_multiexec(miso, head, seg_num);
	else
		exit_status = miso_exec(miso, head);
}

int miso_exec(t_miso *shell, t_token *head);
{

}

int miso_multiexec(t_miso *shell, t_token *head, int p_num)
{
	char	**cmd;
	int		p[2];
	t_token	*trav;
	int		guide;

	guide = 0;
	trav = head;

	while (guide < p_num)
	{
		miso_set_channel(head, p);
	}
}

int miso_set_channel(t_token *head, int pipe[])
{
	int     fdin;
	int     fdout;

	fdin = 0;
	fdout = 1;
}

char **miso_argv(t_token *head)
{
	t_token *trav;
	int		argc;
	char	*argv;

	trav = head;
	argc = 1;
	while(trav->next != NULL && trav->type != CMD && trav->type != BLTIN)
		trav = trav->next;
	if (trav->type != BLTIN)
		miso_pathfinder(trav->str);
	while(trav->next != NULL && trav->type != PIPE)
	{
		if (trav->type == ARG)
			argc++;
		trav = trav->next;
	}
	argv = ft_calloc(argc + 1, sizeof(char *));
	miso_checknfree(NULL, argv, NULL, NULL);
	return (miso_populate(argv, argc, head));
}

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
argv buffer, in order to set in order the commands and its arguments
essentially creating the argument vector that will be 

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
