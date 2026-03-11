/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miso_exec_utils_charlie.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-san- <lde-san-@student.42porto.co      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/05 00:11:16 by lde-san-          #+#    #+#             */
/*   Updated: 2026/03/11 21:23:48 by lde-san-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/miso.h"

void	miso_free_matrix(char **matrix);
int		miso_freenret(void *free1, void *free2, int p_err, int ret);
void    miso_checknfree1d(t_shell *m, char *check, void *free1, char **free2);
void    miso_checknfree2d(t_shell *m, char **check, void *free1, char **free2);
void    miso_get_argv_nrun(t_shell *miso, t_token *head);

void	miso_checknfree1d(t_shell *m, char *check, void *free1, char **free2)
{
	if (check)
		return ;
	perror(BLOD PROMPT RSET);
	if (free1)
		free(free1);
	if (free2)
		miso_free_matrix(free2);
	misoverse_free_exit(m, 0, 2);
}
/* Mainly for checking memory allocations, this option takes either a * or
** pointer to check and one to free previous dependencies if necessary. The
function will print the message from errno if necessary and exit with
EXIT_FAILURE */

void	miso_checknfree2d(t_shell *m, char **check, void *free1, char **free2)
{
	if (check)
		return ;
	perror(BLOD PROMPT RSET);
	if (free1)
		free(free1);
	if (free2)
		miso_free_matrix(free2);
	misoverse_free_exit(m, 0, 2);
}

int	miso_freenret(void *free1, void *free2, int p_err, int ret)
{
	if (p_err)
		perror(BLOD PROMPT RSET);
	if (free1)
		free(free1);
	if (free2)
		free(free2);
	return (ret);
}
/* Mainly for failed memory allocations, this option takes * pointers
to free previous dependencies if necessary. The function will 
print the message from errno if the p_err flag is set to 1, and return
the value passed on ret. */

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

void	miso_get_argv_nrun(t_shell *miso, t_token *head)
{
	char    **cmd;
	int		command_status;

	cmd = NULL;
	command_status = miso_argv(miso, head, cmd);
	if (command_status)
		misoverse_free_exit(miso, 0, command_status);
	miso_call_program(miso, cmd, head);
	return ;
}
