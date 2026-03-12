/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miso_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-san- <lde-san-@student.42porto.co      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/07 20:08:23 by lde-san-          #+#    #+#             */
/*   Updated: 2026/03/12 23:43:42 by lde-san-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/miso.h"

static void	miso_print_env_format(char *writer);

int	miso_env(t_shell *miso, char **argv)
{
	int		index;
	char	*writer;

	index = 0;
	if (!(miso->envp) || !argv)
		return (0);
	while ((miso->envp)[index])
	{
		writer = (miso->envp)[index];
		while (*writer && *writer != '=')
			writer++;
		if (*writer == '=' && !miso_isvarinexp(miso->exp, (miso->envp)[index]))
		{
			writer = (miso->envp)[index];
			miso_print_env_format(writer);
		}
		index++;
	}
	return (0);
}
/* Prints all exported variables, stored in envp, that have an
asigned value, regardless of other arguments, and will always 
return 0. The function is designed to format different parts of 
each variable in different colors to help with readability and 
farm some aura. */

static void	miso_print_env_format(char *writer)
{
	racc_print(1, PURP);
	while (*writer && *writer != '=')
		write(1, (writer)++, 1);
	racc_print(1, BABY);
	if (*writer == '=')
		write(1, (writer)++, 1);
	racc_print(1, ORNG);
	while (*writer)
		write(1, (writer)++, 1);
	racc_print(1, RSET"\n");
	return ;
}
