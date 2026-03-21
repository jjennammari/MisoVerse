/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miso_export_utils_charlie.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-san- <lde-san-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/19 12:39:25 by lde-san-          #+#    #+#             */
/*   Updated: 2026/03/19 18:15:02 by lde-san-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/miso.h"

void		miso_rectify_exp(t_shell *miso);
static int	miso_exp_assigned(t_shell *miso, int index);
static int	miso_exp_unnassigned(t_shell *miso, int index);
static int	miso_envp_unnassigned(t_shell *miso, int index);

void miso_rectify_exp(t_shell *miso)
{
	int guide;
	int index;

	guide = 0;
	while (miso->exp[guide])
	{
		index = 0;
		if (miso_find_envar(miso->envp, miso->exp[guide], &index))
		{
			if (ft_strchr(miso->envp[index], '='))
			{
				if (miso_exp_assigned(miso, guide))
					misoverse_free_exit(miso, 1, 2);
			}
			else if (miso_exp_unnassigned(miso, guide))
				misoverse_free_exit(miso, 1, 2);
		}
		else if (miso_envp_unnassigned(miso, guide))
			misoverse_free_exit(miso, 1, 2);
		guide++;
	}
	return ;
}

static int	miso_envp_unnassigned(t_shell *miso, int index)
{
	if (ft_strchr(miso->exp[index], '='))
		if (miso_exp_unnassigned(miso, index))
			return (1);
	if(miso_add_envar(&(miso->envp), miso->exp[index], "") == -1)
		return (1);
	return (0);
}

static int  miso_exp_unnassigned(t_shell *miso, int index)
{
	char    *neo;
	int		guide;
	char	*temp;

	if (!ft_strchr(miso->exp[index], '='))
		return (0);
	neo = ft_calloc(ft_strlen(miso->exp[index]), sizeof(char));
	if (!neo)
		return (1);
	guide = 0;
	while (miso->exp[index][guide] != '=')
	{
		neo[guide] = miso->exp[index][guide];
		guide++;
	}
	temp = miso->exp[index];
	miso->exp[index] = neo;
	free(temp);
	return (0);
}

static int	miso_exp_assigned(t_shell *miso, int index)
{
	char	*neo;
	int		guide;
	char	*temp;

	if (ft_strchr(miso->exp[index], '='))
		return (0);
	neo = ft_calloc(ft_strlen(miso->exp[index]) + 2, sizeof(char));
	if (!neo)
		return (1);
	guide = 0;
	while (miso->exp[index][guide])
	{
		neo[guide] = miso->exp[index][guide];
		guide++;
	}
	neo[guide] = '=';
	temp = miso->exp[index];
	miso->exp[index] = neo;
	free(temp);
	return (0);
}
