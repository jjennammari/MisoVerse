/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miso_pwd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-san- <lde-san-@student.42porto.co      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/02 19:09:14 by lde-san-          #+#    #+#             */
/*   Updated: 2026/03/18 22:07:33 by lde-san-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/miso.h"

int	miso_pwd(t_shell *miso, char **argv)
{
	char	*path_wd;
	int		alloc;

	(void)argv;
	alloc = 0;
	path_wd = miso_getenv("PWD", miso->envp);
	if (!path_wd)
	{
		path_wd = getcwd(NULL, 0);
		alloc++;
	}
	if (!path_wd)
	{
		racc_print(2, ORNG"pwd"RSET": "BLOD PROMPT RSET": ");
		racc_print(2, "Can't resolve present working directory\n");
		return (1);
	}
	else
		racc_print(1, "%s\n", path_wd);
	if (alloc)
		free(path_wd);
	return (0);
}
/* The function calls "getcwd(NULL, 0)" to have it allocate memory dynamically
and store in it the absolute path to the current working directory, that it
gets from the kernel. The result is then printed with a trailing newline, and
free()'d immediately after. The function will return 1 in error and 0 on 
success, printing the corresponding error message if necessary. */
