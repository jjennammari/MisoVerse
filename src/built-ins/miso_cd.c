/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miso_cd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-san- <lde-san-@student.42porto.co      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/03 13:25:13 by lde-san-          #+#    #+#             */
/*   Updated: 2026/02/05 01:29:56 by lde-san-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/miso.h"

int miso_cd(t_shell *miso, char **cmd)
{
	int	arc;
	char *pwd;

	arc = 0;
	pwd = ft_strjoin(NULL, miso_getenv("PWD=", miso->envp))
	while (cmd[arc])
		arc++;
	if (arc == 2)
		return (miso_chdir_to_arg(miso, cmd[1], ft_strlen(cmd[1]), pwd));
	if (arc == 1)
		return (miso_chdir_to_home(miso, miso_getenv("HOME=", miso->envp)));
	racc_print(2, BLOD"PROMPT "MINT"cd: "RSET"too many arguments\n");
	return (1);
}

int	miso_addorupdate(char **envp, char *key, char *varlue)
{
	int exit_code;

	exit_code = miso_add_envar(envp, key, varlue);
	if (exit_code == -1)
		return (1);
	if (exit_code == 1)
	{
		if (miso_envar_update(envp, key, varlue) == -1)
			return (1);
	}
	return (0);
}

static int	miso_chdir_to_arg(t_shell *m, char *p, int p_len, char *pwd)
{
	char	*cwd;
	int		exit_code;

	if (p_len == 1 && p[0] == '-')
	{
		if (chdir(miso_getenv("OLDPWD=", m->envp)) == -1)
		{
			racc_print(2, BLOD"PROMPT "MINT"cd: "RSET"OLDPWD not set\n");
			free(pwd);
			return (1);
		}
		if(miso_addorupdate(m->envp, "OLDPWD=", pwd))
			return (miso_freenret(pwd, NULL, 1, 1));
		cwd = getcwd(NULL, 0);
		if (!cwd)
			return (miso_freenret(pwd, NULL, 1, 1));
		if(miso_addorupdate(m->envp, "PWD=", cwd))
			return(miso_freenret(pwd, cwd, 1, 1));
	}
	// maybe double check you didn't mess tings up. But is looking solid
	// as it is rn. Maybe confirm with bash behaviour. In any case, you are
	// thinking right now on moving this handling of "-" to its own helper
	// and then follow a similar logic for the "any other dir" logic.
	// Good luck, hope you had a nice rest <3

}
