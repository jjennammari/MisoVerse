/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miso_launch.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-san- <lde-san-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/21 18:28:07 by lde-san-          #+#    #+#             */
/*   Updated: 2026/01/22 20:20:43 by lde-san-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miso.h"

int	miso_launch(t_shell *miso, t_token *head)
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

int miso_exec(t_shell *miso, t_token *head);
{

}

int miso_multiexec(t_shell *miso, t_token *head, int p_num)
{
	char	*cmd[];
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
	char	*comand;

	trav = head;
	argc = 1;
	while(trav->next != NULL && (trav->type != CMD || trav->type != BLTIN))
		trav = trav->next;
	comand = miso_pathfinder(trav->str);
}

char *miso_pathfinder(char *cmd);
{
	char	**dirs;
	int		guide;
	char	*pathname;
	char	*temp;

	if (ft_strchr(cmd_in, '/'))
		return (cmd);
	dirs = ft_split(getenv("PATH"), ':');
	miso_checknfree(NULL, dirs, NULL, NULL);
	temp = ft_strjoin("/", cmd);
	miso_checknfree(temp, NULL, NULL, dirs);
	pathname = miso_pathmatch(dirs, temp);
	miso_checknfree(pathname, NULL, temp, dirs);
	free(temp);
	miso_free_matrix(dirs);
	miso_customs(pathname, access(pathname, F_OK));
}

void miso_customs(char *program, int exists)
{
	if (exists)
	{
		free(program);
		exit(1);
	}
	// Check here if the file is a folder to write the correct message
}

char	*miso_pathmatch(char **dirs, char *temp_filename)
{
	int		guide;
	char	*pathname;

	if (!temp_filename || !dirs)
		return (NULL);
	guide = 0;
	pathname = ft_strjoin(dirs[guide], temp_filename);
	if (!pathname)
		return (NULL);
	while (access(pathname, F_OK) && dirs[guide])
	{
		guide++;
		if (!dirs[guide])
			break ;
		free(pathname);
		pathname = ft_strjoin(dirs[guide], temp_filename);
		if (!pathname)
			return (NULL);
	}
	return (pathname);
}

void miso_checknfree(void *check1, void **check2, void *free1, void **free2)
{
	if (check1 || check2)
		return ;
	perror(BLOD""PROMPT""RSET);
	if (free1)
		free(free1);
	if (free2)
		miso_free_matrix(free2);
	exit(1);
}

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
}

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
