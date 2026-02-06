/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miso_environment_utils_beta.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-san- <lde-san-@student.42porto.co      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/06 22:11:44 by lde-san-          #+#    #+#             */
/*   Updated: 2026/02/06 23:25:53 by lde-san-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/miso.h"

int	miso_env_addorupdate(char ***envp, char *key, char *varlue)
{
	int exit_code;

	exit_code = miso_add_envar(envp, key, varlue);
	if (exit_code == -1)
		return (1);
	if (exit_code == 1)
	{
		if (miso_envar_update(*envp, key, varlue) == -1)
			return (1);
	}
	return (0);
}
/* Attempts to both add and update the variable passed, ensuring 
that the action that's necessary is taken without the caller 
needing to worry about it. Also simplifies the return values for
these functions, making it so that it'll only return the basic 1
on error 0 on success. */

char	*miso_extract_variable(char **envp, const char *key, int key_len)
{
	char	*envar;
	int		guide;

	envar = miso_find_envar(envp, key, key_len, &guide);
	if(!envar)
		return (NULL);
	while (envp[guide])
	{
		envp[guide] = envp[guide + 1];
		guide++;
	}
	guide = 0;
	while (envar[key_len + guide])
	{
		envar[guide] = envar[key_len + guide];
		guide++;
	}
	envar[guide] = '\0';
	return (envar);
}

char	*miso_remove_envar(char **envp, const char *key, int key_len)
{
	char	*envar;
	int		guide;

	envar = miso_find_envar(envp, key, key_len, &guide);
	if(!envar)
		return (NULL);
	while (envp[guide])
	{
		envp[guide] = envp[guide + 1];
		guide++;
	}
	guide = 0;
	return (envar);
}
