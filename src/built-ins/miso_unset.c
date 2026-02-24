/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miso_unset.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-san- <lde-san-@student.42porto.co      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/07 18:52:00 by lde-san-          #+#    #+#             */
/*   Updated: 2026/02/20 18:07:03 by lde-san-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/miso.h"

int			miso_unset(t_shell *miso, char **argv);
static int	miso_unset_loop(t_shell *miso, char **argv);

int	miso_unset(t_shell *miso, char **argv)
{
	int		arc;
	char	**og_envp;

	arc = 0;
	while (argv[arc])
		arc++;
	if (arc == 1)
		return (0);
	og_envp = miso->envp;
	miso->envp = miso_matrixdup(og_envp);
	if (!miso->envp)
	{
		miso->envp = og_envp;
		return (1);
	}
	if (miso_unset_loop(miso, argv))
	{
		miso_free_matrix(miso->envp);
		miso->envp = og_envp;
		return (1);
	}
	miso_free_matrix(og_envp);
	return (0);
}
/* Creates a copy of the envp, to ensure that no changes go to the
original in case the function fails half-way through execution. If
the directory is changed successfully, it will update the envp and
free the unchanged copy. It returns 1 on any type of failure and 0
on  success. It returns  0  early if the program is called with no 
arguments.*/

static int	miso_unset_loop(t_shell *miso, char **argv)
{
	int		index;
	char	*key;
	char	*ex_envar;

	index = 1;
	while (argv[index])
	{
		key = argv[index];
		if (!ft_strchr(argv[index], '='))
		{
			ex_envar = miso_remove_envar(miso->envp, key);
			miso_removexp(miso, key);
			if (ex_envar)
				free(ex_envar);
			free(key);
		}
		index++;
	}
	return (0);
}
/* Loops through the argv array appending a "=" at the end of each
argument to pass a copy of the *key to a function that will remove 
the variable from envp, if it finds it, and return a pointer to it.
Both the pointer and the copy of the key are freed as the loop
continues, ensuring all "valid" arguments are removed. The function
will return 0 once the end of the array has been reached, or 1 in 
case of an allociation error. */
