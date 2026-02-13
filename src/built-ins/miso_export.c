/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miso_export.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-san- <lde-san-@student.42porto.co      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/07 21:08:32 by lde-san-          #+#    #+#             */
/*   Updated: 2026/02/13 21:44:59 by lde-san-         ###   ########.fr       */
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
		if (miso_export_sort(envp_clone, envp_len) && !*(miso->envp))
			return (miso_free_matrix(envp_clone), 0);
		else
			return (1);
	}
	if (miso_parsenexport(envp_clone, argv))
		return (1);
	miso_free_matrix(miso->envp);
	miso->envp = envp_clone;
	return (0);
}
