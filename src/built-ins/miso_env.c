/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miso_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-san- <lde-san-@student.42porto.co      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/07 20:08:23 by lde-san-          #+#    #+#             */
/*   Updated: 2026/02/07 20:49:01 by lde-san-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/miso.h"

int	miso_env(t_shell *miso, char **argv)
{
	int		index;
	char	*writer;

	index = 0;
	if (!(miso->envp))
		return (0);
	while ((miso->envp)[index])
	{
		writer = (miso->envp)[index];
		while (*writer && *writer != '=')
			racc_print(1, PURP"%c", writer++);
		if (*writer == '=')
			racc_print(1, BABY"%c", writer++);
		while (*writer)
			racc_print(1, ORNG"%c", writer++);
		racc_print(1, RSET"\n");
		index++;
	}
	return (0);
}
/* Prints all variables stored in envp regardless of other 
arguments, and will always return 0. The function is designed
to format different parts of each variable in different colors
to help with readability and farm some aura. */
