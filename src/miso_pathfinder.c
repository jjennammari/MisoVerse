/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miso_pathfinder.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-san- <lde-san-@student.42porto.co      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/28 19:35:38 by lde-san-          #+#    #+#             */
/*   Updated: 2026/04/01 03:42:24 by lde-san-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/miso.h"

char		*miso_pathmatch(char **dirs, char *temp_filename);
int			miso_argv(t_shell *miso, t_token *head, char ***cmd);
static int	miso_pathfinder(t_shell *miso, char **c, int *p_set);
void		miso_customs(char **program, int *p_set);
static int	miso_populate(t_shell *m, char ***argv, int argc, t_token *head);

int	miso_argv(t_shell *miso, t_token *head, char ***cmd)
{
	int		argc;
	int		path_set;

	argc = 1;
	path_set = 0;
	*cmd = NULL;
	miso->sgmnt = head;
	while (head && head->type != SYS_CMD && head->type != BLT_CMD)
		head = head->next;
	if (head->type != BLT_CMD && miso_pathfinder(miso, &head->str, &path_set))
		return (path_set);
	while (head && head->type != PIPE)
	{
		if (head->type == RD_IN || head->type == RD_OUT || head->type == APPEND)
		{
			head = head->next->next;
			continue ;
		}
		if (head && head->type == ARG)
			argc++;
		if (head)
			head = head->next;
	}
	return (miso_populate(miso, cmd, argc, miso->sgmnt));
}
/*Advances until it finds the comand, and if is not a built-in, or has
a literal path, it updates the str* with the path to the program. Then it 
counts the arguments passed in order to allocate the argv 2D array and 
populate it with the strings from the list. */

static int	miso_pathfinder(t_shell *miso, char **c, int *p_set)
{
	char	**dirs;
	char	*path;

	path = miso_getenv("PATH=", miso->envp);
	if (ft_strchr(*c, '/') || !path || !(*path))
		return (miso_customs(c, p_set), *p_set);
	if (!(*c) || !(*(*c)))
	{
		*p_set = 127;
		write(2, BLOD PROMPT RSET": "MINT, 58);
		write(2, *c, ft_strlen(*c));
		write(2, RSET": Command not found, maybe try installing it...\n", 54);
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
	write(2, BLOD PROMPT RSET": "MINT"\n", 57);
	write(2, ((temp_filename) + 1), ft_strlen(temp_filename + 1));
	write(2, RSET": command not found\n", 26);
	return (temp_filename);
}
/* Iterates through all the provided directories, checking if the file
passed exists. It will return the full path to the program or NULL if 
it doesn't find it, assuming that the command passed is not built-in */

static int	miso_populate(t_shell *m, char ***argv, int argc, t_token *h)
{
	int		guide;

	*argv = ft_calloc(argc + 1, sizeof(char *));
	miso_checknfree2d(m, *argv, NULL, NULL);
	(*argv)[argc] = NULL;
	guide = 0;
	while (guide < argc && h && h->type != PIPE)
	{
		if (h->type == RD_IN || h->type == RD_OUT || h->type == APPEND)
		{
			h = h->next->next;
			continue ;
		}
		if (h && (h->type == SYS_CMD || h->type == BLT_CMD || h->type == ARG))
		{
			(*argv)[guide] = ft_strdup(h->str);
			miso_checknfree1d(m, (*argv)[guide], NULL, *argv);
			guide++;
		}
		if (h)
			h = h->next;
	}
	m->sgmnt = NULL;
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
		if (errno == ENOENT)
			*p_set = 127;
		else
			*p_set = 126;
		racc_print(2, BLOD PROMPT RSET": "ORNG"%s", *cmd);
		perror(RSET);
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
	miso_eval_pset(cmd, *p_set);
	return ;
}
/* It checks the metadata found by stat, to check if the path goes to a
program or a directory, in order to print the correct error message and
exit accordingly. The function is meant to be called with with the 
access() function on the second parameter, to validate if the "object"
doesn't exist. */
