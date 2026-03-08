/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miso_environment_utils_charlie.c                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-san- <lde-san-@student.42porto.co      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/22 15:18:15 by lde-san-          #+#    #+#             */
/*   Updated: 2026/03/08 01:07:04 by lde-san-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/miso.h"

static void	miso_update_shlvl(char ***envp);
void		miso_keyvariables_init(char ***envp);
static void	miso_path_confirm(char ***envp, char *paths);

void	miso_keyvariables_init(char ***envp)
{
	char	*cwd;

	cwd = getcwd(NULL, 0);
	miso_checknfree(cwd, NULL, NULL, *envp);
	if ((miso_add_envar(envp, "OLDPWD", "")) == -1)
		miso_checknfree(NULL, NULL, cwd, *envp);
	if (miso_env_addorupdate(envp, "PWD=", cwd))
		miso_checknfree(NULL, NULL, cwd, *envp);
	free(cwd);
	miso_update_shlvl(envp);
	miso_path_confirm(envp, miso_getenv("PATH", *envp));
	return ;
}
/* Checks and initializes the key varibles that should be set on 
start up in case they come unset */

static void	miso_path_confirm(char ***envp, char *paths)
{
	char	*p;

	if (paths)
		return ;
	p = "/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin";
	if ((miso_add_envar(envp, "PATH=", p)) == -1)
		miso_checknfree(NULL, NULL, NULL, *envp);
	return ;
}
/* Confirms that there's a PATH variable in envp, and if
there isn't it initializes it with a default string of most
common directories */

static void	miso_update_shlvl(char ***envp)
{
	char	*new_lvl;
	int		crnt_lvl;

	if (!miso_find_envar(*envp, "SHLVL", NULL))
	{
		miso_add_envar(envp, "SHLVL=", "1");
		return ;
	}
	crnt_lvl = ft_atoi(miso_getenv("SHLVL", *envp));
	new_lvl = ft_itoa(crnt_lvl + 1);
	if (!new_lvl)
		miso_checknfree(NULL, NULL, new_lvl, *envp);
	if (miso_envar_update(*envp, "SHLVL=", new_lvl) != 0)
		miso_checknfree(NULL, NULL, new_lvl, *envp);
	free(new_lvl);
	return ;
}
/* It will read the number stored in the SHLVL variable, to
add 1 to it. If there isn't one, it creates it initializing
its value to 1 */
