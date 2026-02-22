/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miso_cd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-san- <lde-san-@student.42porto.co      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/03 13:25:13 by lde-san-          #+#    #+#             */
/*   Updated: 2026/02/22 11:59:48 by lde-san-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/miso.h"

static int	miso_chdir_oldpwd(t_shell *m);
int			miso_cd(t_shell *miso, char **argv);
static int	miso_chdir(t_shell *miso, char **cmd, int arc);
static int	miso_chdir_to_arg(t_shell *m, char *p, int p_len);

int	miso_cd(t_shell *miso, char **argv)
{
	int		arc;
	char	**og_envp;

	arc = 0;
	while (argv[arc])
		arc++;
	og_envp = miso->envp;
	miso->envp = miso_matrixdup(og_envp);
	if (!miso->envp)
	{
		miso->envp = og_envp;
		return (1);
	}
	if (miso_chdir(miso, argv, arc))
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
on success. */

static int	miso_chdir(t_shell *miso, char **cmd, int arc)
{
	char	*home;

	if (arc == 2)
		return (miso_chdir_to_arg(miso, cmd[1], ft_strlen(cmd[1])));
	if (arc == 1)
	{
		home = miso_getenv("HOME", miso->envp);
		if (!home || !(*home))
			racc_print(2, BLOD"PROMPT "MINT"cd: "RSET"HOME not set\n");
		else
			return (miso_chdir_to_arg(miso, home, 0));
		return (1);
	}
	racc_print(2, BLOD"PROMPT "MINT"cd: "RSET"too many arguments\n");
	return (miso_freenret(NULL, NULL, 0, 1));
}
/* Changes the current working directory to the one specified by the
path in cmd[1]. The path being absolute or relative. It also handles
no path by sending the user home and "cd -" to send the user to 
OLDPWD. On success, it returns 0 and updates the $OLDPWD and $PWD 
environment variables accordingly. Otherwise, it will return 1 for
any type of error, after printing the corresponding error message. */

static int	miso_chdir_to_arg(t_shell *m, char *p, int p_len)
{
	char	*cwd;
	char	*pwd;

	if (p_len == 1 && p[0] == '-')
		return (miso_chdir_oldpwd(m));
	if (chdir(p) == -1)
		return (miso_freenret(NULL, NULL, 1, 1));
	pwd = miso_extract_variable(m->envp, "PWD=");
	if (miso_env_addorupdate(&(m->envp), "OLDPWD=", pwd))
		return (miso_freenret(pwd, NULL, 1, 1));
	cwd = getcwd(NULL, 0);
	if (!cwd)
		return (miso_freenret(pwd, NULL, 1, 1));
	if (miso_env_addorupdate(&(m->envp), "PWD=", cwd))
		return (miso_freenret(pwd, cwd, 1, 1));
	return (miso_freenret(pwd, cwd, 0, 0));
}
/* Changes the present working directory PWD, to the one specified
in the path argument "p". It also checks for the edge case "cd -"
to call the function that will change to the OLDPWD. After changing,
it updates the PWD and OLDPWD with its new values. It returns 1 on
any type of failure and 0 on success. */

static int	miso_chdir_oldpwd(t_shell *m)
{
	char	*old_pwd;

	old_pwd = miso_getenv("OLDPWD=", m->envp);
	if (!old_pwd)
	{
		racc_print(2, BLOD"PROMPT "MINT"cd: "RSET"OLDPWD not set\n");
		return (1);
	}
	if (miso_chdir_to_arg(m, old_pwd, 0))
		return (1);
	racc_print(1, "%s\n", miso_getenv("PWD=", m->envp));
	return (0);
}
/* Looks specifically at the OLDPWD variable to call the
miso_chdir_to_arg fuction with the correct path. After
the directory has been changed, it will print the path
that was stored in PWD. It returns 1 on any type of 
failure and 0 on success. */
