/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miso_export.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-san- <lde-san-@student.42porto.co      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/07 21:08:32 by lde-san-          #+#    #+#             */
/*   Updated: 2026/02/22 21:20:06 by lde-san-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/miso.h"

int	miso_export(t_shell *miso, char **argv)
{
	int		envp_len;
	char	**envp_clone;

	envp_len = 0;
	envp_clone = miso_matrixdup(miso->envp);
	while ((miso->envp)[envp_len])
		envp_len++;
	if (argv && argv[0] && !argv[1])
	{
		if (miso_export_sort(miso, envp_clone, envp_len) && !*(miso->envp))
			return (miso_free_matrix(envp_clone), 0);
		else
			return (1);
	}
	if (miso_parsenexport(miso, &envp_clone, argv))
		return (1);
	miso_free_matrix(miso->envp);
	miso->envp = envp_clone;
	return (0);
}

int miso_parsenexport(t_shell *miso, char ***envp, char **argv)
{
	int		guide;
	int		exit_code;
	char	*key;

	guide = 0;
	exit_code = 0;
	while (argv[guide])
	{
		if (miso_exparse(argv[guide]))
		{
			exit_code = 1;
			guide++;
			continue ;
		}
		key = miso_get_key(argv[guide]);
		if (!key)
			return (miso_freenret(NULL, NULL, 1, 1);
		if (miso_exp_add_or_update(miso, envp, (argv[guide]) + ft_strlen(key))
			return (miso_freenret(key, NULL, 1, 1))
		free(key);
		guide++;
	}
	return (exit_code);
}

int	miso_exp_add_or_update(t_shell *miso, char ***envp, char *key, char *var)
{
	char	key_term;

	key_term = key[ft_strlen(key)];
	if (!key_term)
	{
		if (miso_env_addorupdate(envp, key, "");
			return (1);
	}
	else
	{
		if (miso_env_addorupdate(envp, key, var);
			return (1);
	}
	if (miso_addexp(miso, key))
		return (1);
	return (0);
}
