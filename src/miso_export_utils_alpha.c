/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miso_export_utils_alpha.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-san- <lde-san-@student.42porto.co      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/14 16:23:11 by lde-san-          #+#    #+#             */
/*   Updated: 2026/02/14 17:56:29 by lde-san-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/miso.h"

void	miso_exp_innit(t_shell *miso)
{
	int	guide;

	guide = 0;
	while((miso->envp)[guide])
		guide++;
	miso->exp = ft_calloc(guide + 1, sizeof(char *));
	miso_checknfree(NULL, miso->exp, NULL, miso->envp);
	(miso->exp)[guide] = NULL;
	while(guide-- > 0)
	{
		(miso->exp)[guide] = miso_get_key((miso->envp)[guide]);
		if (!(miso->exp)[guide])
		{
			perror(BLOD"PROMPT"RSET);
			miso_free_matrix(miso->exp);
			miso_free_matrix(miso->envp);
			exit(1);
		}
	}
	return ;
}

int	miso_addexp(t_shell *miso, char *key)
{
	int		guide;
	char	**temp;

	if (miso_expcheck(miso->exp, key, &guide))
		return (0);
	temp = miso->exp;
	miso->exp = ft_calloc(++guide + 1, sizeof(char *));
	if (!miso->exp)
	{
		miso->exp = temp;
		return (1);
	}
	miso->exp[guide--] = NULL;
	miso->exp[guide] = ft_strdup(key);
	if (!miso->exp[guide])
	{
		miso_free_matrix(miso->exp);
		miso->exp = temp;
		return (1);
	}
	while (guide-- > 0)
		miso->exp[guide] = temp[guide];
	free(temp);
	return (0);
}

void	miso_removexp(t_shell *miso, char *key)
{
	int		guide;
	char	*temp;

	if (!miso_expcheck(miso->exp, key, &guide))
		return ;
	temp = (miso->exp)[guide];
	while ((miso->exp)[guide])
	{
		(miso->exp)[guide] = (miso->exp)[guide + 1];
		guide++;
	}
	free(temp);
	return ;
}

char	*miso_expcheck(char **exp, char *key, int *index)
{
	int	i;
	int	*guide;

	if (!index)
		guide = &i;
	else
		guide = index;
	*guide = 0;
	while (exp[*guide])
	{
		if (!miso_envarcmp(exp[*guide], key))
			return (exp[*guide]);
		(*guide)++;
	}
	return (NULL);
}
