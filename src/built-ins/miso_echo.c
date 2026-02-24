/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miso_echo.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-san- <lde-san-@student.42porto.co      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/02 20:23:46 by lde-san-          #+#    #+#             */
/*   Updated: 2026/02/13 20:11:59 by lde-san-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/miso.h"

static int	miso_n_validate(char *arg);
int			miso_echo(t_shell *miso, char **argv);

int	miso_echo(t_shell *miso, char **argv)
{
	int	guide;
	int	nl_ending;

	guide = 1;
	(void)miso;
	nl_ending = miso_n_validate(argv[guide]);
	if (!nl_ending)
	{
		while (argv[guide] && !miso_n_validate(argv[guide]))
			guide++;
	}
	while (argv[guide])
	{
		if (!argv[guide + 1])
			racc_print(1, "%s", argv[guide]);
		else
			racc_print(1, "%s ", argv[guide]);
		guide++;
	}
	if (nl_ending)
		racc_print(1, "\n");
	return (0);
}
/* The subject specifies that only explicitly requested behavior is required.
While environment variable expansion is mentioned, escape sequence expansion
is not. Therefore, this implementation of echo treats backslashes ('\')
literally, as regular characters. This is especially reasonable since escape
processing is typically handled by the shell itself, meaning echo would
receive them literally anyway. The function always returns 0. It skips all
leading "-n" flags, if present, to determine whether the trailing newline 
should be printed. */

static int	miso_n_validate(char *arg)
{
	int	guide;

	guide = 0;
	if (!arg || arg[guide] != '-')
		return (1);
	guide++;
	if (arg[guide] != 'n')
		return (1);
	while (arg[guide] == 'n')
		guide++;
	if (arg[guide])
		return (1);
	return (0);
}
/*Checks if the arg passed is a valid "-n" flag configuration. Returns 0
if it is, and 1 if it is not.*/
