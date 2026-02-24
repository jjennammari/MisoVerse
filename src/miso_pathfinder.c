/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miso_pathfinder.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-san- <lde-san-@student.42porto.co      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/28 19:35:38 by lde-san-          #+#    #+#             */
/*   Updated: 2026/02/04 21:49:04 by lde-san-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/miso.h"

char		**miso_argv(t_token *head, char **envp);
static void	miso_pathfinder(char **cmd, char **envp);
static void	miso_customs(char *program, int doesnt_exist);
static char	*miso_pathmatch(char **dirs, char *temp_filename);
static char	**miso_populate(char **argv, int argc, t_token *head);

char	**miso_argv(t_token *head, char **envp)
{
	t_token	*trav;
	int		argc;
	char	**argv;

	trav = head;
	argc = 1;
	while (trav && trav->type != SYS_CMD && trav->type != BLT_CMD)
		trav = trav->next;
	if (trav->type != BLT_CMD)
		miso_pathfinder(&trav->str, envp);
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

static void	miso_pathfinder(char **cmd, char **envp)
{
	char	**dirs;
	char	*path_name;
	char	*temp;
	char	*old_str;

	if (ft_strchr(*cmd, '/'))
		return ;
	dirs = ft_split(miso_getenv("PATH=", envp), ':');
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

static char	*miso_pathmatch(char **dirs, char *temp_filename)
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

static char	**miso_populate(char **argv, int argc, t_token *head)
{
	t_token	*trav;
	int		guide;

	argv[argc] = NULL;
	trav = head;
	guide = 0;
	while (guide < argc && trav && trav->type != PIPE)
	{
		if (trav->type == SYS_CMD || trav->type == BLT_CMD || trav->type == ARG)
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
execve(). It assumes that there is only one comand of either type SYS_CMD
or BLT_CMD, and that the conditions are optimally configured so all 
arguments come after the comand. */

static void	miso_customs(char *program, int doesnt_exist)
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
