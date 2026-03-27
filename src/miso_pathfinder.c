/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miso_pathfinder.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-san- <lde-san-@student.42porto.co      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/28 19:35:38 by lde-san-          #+#    #+#             */
/*   Updated: 2026/03/26 18:38:21 by lde-san-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/miso.h"

char		*miso_pathmatch(char **dirs, char *temp_filename);
int			miso_argv(t_shell *miso, t_token *head, char ***cmd);
static int	miso_pathfinder(t_shell *miso, char **c, int *p_set);
void		miso_customs(char **program, int *p_set);
static int	miso_populate(t_shell *m, char **argv, int argc, t_token *head);

int	miso_argv(t_shell *miso, t_token *head, char ***cmd)
{
	t_token	*trav;
	int		argc;
	int		path_set;

	trav = head;
	argc = 1;
	path_set = 0;
	*cmd = NULL;
	while (trav && trav->type != SYS_CMD && trav->type != BLT_CMD)
		trav = trav->next;
	if (trav->type != BLT_CMD && miso_pathfinder(miso, &trav->str, &path_set))
		return (path_set);
	while (trav && trav->type != PIPE)
	{
		if (trav->type == RD_IN || trav->type == RD_OUT || trav->type == APPEND
			|| trav->type == HEREDOC)
			trav = trav->next->next;
		if (trav && trav->type == ARG)
			argc++;
		if (trav)
			trav = trav->next;
	}
	*cmd = ft_calloc(argc + 1, sizeof(char *));
	miso_checknfree2d(miso, *cmd, NULL, NULL);
	return (miso_populate(miso, *cmd, argc, head));
}
/*Advances until it finds the comand, and if is not a built-in, or has
a literal path, it updates the str* with the path to the program. Then it 
counts the arguments passed in order to allocate the argv 2D array and 
populate it with the strings from the list. */

static int	miso_pathfinder(t_shell *miso, char **c, int *p_set)
{
	char	**dirs;
	char	*path;

	if (ft_strchr(*c, '/'))
		return (miso_customs(c, p_set), *p_set);
	path = miso_getenv("PATH=", miso->envp);
	if (!path || !(*path) || !(*c) || !(*(*c)))
	{
		*p_set = 127;
		racc_print(2, BLOD PROMPT RSET": "MINT"%s"RSET, *c);
		racc_print(2, ": Command not found, you could install it though...\n");
		return (1);
	}
	dirs = ft_split(path, ':');
	miso_checknfree2d(miso, dirs, NULL, NULL);
	if (miso_path_err(miso, dirs, c, p_set))
	{
		miso_free_matrix(dirs);
		return (1);
	}
	miso_free_matrix(dirs);
	return (0);
}
/*It splits the directories coming from the PATH variable, in order to
create a strig that will contain the full path to the command passed. 
It will return early if the file contains a "/", as it would indicate
that its being called with a literal path. The path is pre-validated
to ensure that the correct error code and message gets sent. It frees
the memory of the previous string stored in the node, replacing it 
with the newly found path. It assumes that the command passed is not 
built-in*/

char	*miso_pathmatch(char **dirs, char *temp_filename)
{
	int		guide;
	char	*path_name;

	if (!temp_filename || !dirs)
		return (NULL);
	guide = 0;
	path_name = NULL;
	while (dirs[guide])
	{
		if (path_name)
			free(path_name);
		path_name = ft_strjoin(dirs[guide], temp_filename);
		if (!path_name)
			return (NULL);
		if (!access(path_name, F_OK))
			return (path_name);
		guide++;
	}
	free(path_name);
	racc_print(2, BLOD PROMPT RSET": "MINT"%s"RSET, (temp_filename + 1));
	racc_print(2, ": command not found\n");
	return (temp_filename);
}
/* Iterates through all the provided directories, checking if the file
passed exists. It will return the full path to the program or NULL if 
it doesn't find it, assuming that the command passed is not built-in */

static int	miso_populate(t_shell *m, char **argv, int argc, t_token *head)
{
	t_token	*trav;
	int		guide;

	argv[argc] = NULL;
	trav = head;
	guide = 0;
	while (guide < argc && trav && trav->type != PIPE)
	{
		if (trav->type == RD_IN || trav->type == RD_OUT || trav->type == APPEND
			|| trav->type == HEREDOC)
			trav = trav->next->next;
		if (trav && (trav->type == SYS_CMD || trav->type == BLT_CMD
			|| trav->type == ARG))
		{
			argv[guide] = ft_strdup(trav->str);
			miso_checknfree1d(m, argv[guide], NULL, argv);
			guide++;
		}
		if (trav)
			trav = trav->next;
	}
	return (0);
}
/* It traverses through the list as it iterates through the passed
argv buffer, in order to set in order the commands and its arguments.
Essentially creating the argument vector that will be passed to 
execve(). It assumes that there is only one comand of either type SYS_CMD
or BLT_CMD, and that the conditions are optimally configured so all 
arguments come after the comand. */

void	miso_customs(char **cmd, int *p_set)
{
	t_stat	metadata;

	if (stat(*cmd, &metadata) == -1)
	{
		racc_print(2, BLOD PROMPT RSET": "ORNG"%s", *cmd);
		perror(RSET);
		if (errno == ENOENT)
			*p_set = 127;
		else
			*p_set = 126;
	}
	else if (S_ISDIR(metadata.st_mode))
	{
		racc_print(2, BLOD PROMPT": "ORNG"%s"RSET": Is a directory\n", *cmd);
		*p_set = 126;
	}
	else if (access(*cmd, X_OK) == -1)
	{
		racc_print(2, BLOD PROMPT RSET": "ORNG"%s", *cmd);
		perror(RSET);
		*p_set = 126;
	}
	if (*p_set != 126 && *p_set != 127)
		return ;
	free(*cmd);
	*cmd = NULL;
	return ;
}
/* It checks the metadata found by stat, to check if the path goes to a
program or a directory, in order to print the correct error message and
exit accordingly. The function is meant to be called with with the 
access() function on the second parameter, to validate if the "object"
doesn't exist. */
