/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miso_environment_utils_charlie.c                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-san- <lde-san-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/20 16:24:18 by lde-san-          #+#    #+#             */
/*   Updated: 2026/02/20 17:09:08 by lde-san-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/miso.h"

void	miso_envp_exp_filter(char **exp, char **envp)
{
	int		guide;
	char	*not_exported;

	guide = 0;
	while (*envp)
	{
		guide = 0;
		if (!miso_isvarinexp(exp, *envp))
		{
			envp++
			continue ;
		}
		not_exported = *envp;
		while(envp[guide])
		{
			envp[guide] = envp[guide + 1];
			guide++;
		}
		free(not_exported);
	}
	return ;
}
/* The function will evaluate each variable in envp to free any
that are not exported. The function is meant to run in a child 
process, so it only affects the array that will be sent to execve. */
