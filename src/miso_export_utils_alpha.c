/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miso_export_utils_alpha.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-san- <lde-san-@student.42porto.co      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/14 16:23:11 by lde-san-          #+#    #+#             */
/*   Updated: 2026/02/22 20:14:21 by lde-san-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/miso.h"

int		miso_addexp(t_shell *miso, char *key);
int		miso_isvarinexp(char **exp, char *var);
void	miso_removexp(t_shell *miso, char *key);
void	miso_exp_innit(t_shell *miso, char *path_valid);
char	*miso_expcheck(char **exp, char *key, int *index);

void	miso_exp_innit(t_shell *miso, char *path_valid)
{
	int	guide;

	guide = 0;
	while ((miso->envp)[guide])
		guide++;
	miso->exp = ft_calloc(guide + 1, sizeof(char *));
	miso_checknfree(NULL, miso->exp, NULL, miso->envp);
	(miso->exp)[guide] = NULL;
	while (guide-- > 0)
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
	if (!path_valid)
		miso_removexp(miso, "PATH");
	return ;
}
/* Takes a pointer to the Misoverse shell struct and initializes the
export list with all the keys from the variables in the current envp
array. It expects to be called after the envp pointer was initialized 
with a copy of the original. It doesn't have a return value because
it will free the allocated memory and exit in case of an error. Thus 
terminating the shell. In the special case that envp comes empty from 
the caller shell, bash sets a default path for the envirorment, but
this created variable is not exported from startup. For this reason
the function is intended to be called with a pointer to the first  
element of the original **envp, that way if it is NULL, PATH will be
purged immediately from the exp array. */

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
/* It will allocate space for a new export list, increasing its size
by one. The previously allocated keys then get moved to the new array
appending a duplicate of the new one at the end. It returns 1 in case
of an allocation error and 0 on success. If the key is already in the
array, it will return successfully. */

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
/* It will look for the key passed as a parameter, inside the current
export array. If it finds it, it will remove it by shifting all remaining
pointers. Making the array end with 2 NULL pointers. Then it will return 
freeing the extracted variable in the process. Either that or it will
return early if the envirorment variable can't be found. */

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
/* It searches for the *key variable inside of **exp. It will then
return the pointer to the variable or NULL if it doesn't find it. As
it searches the variable, it will update the guide variable it
received (or a local one if the int *index pointer is set to NULL),
so after execution, the caller will either have the index of where
the variable is in the array or the current full length of **exp. */

int	miso_isvarinexp(char **exp, char *var)
{
	int	index;
	int	guide;

	index = 0;
	while (exp[index])
	{
		guide = 0;
		while (exp[index][guide] && var[guide] && exp[index][guide] != '='
			&& var[guide] != '=' && exp[index][guide] == var[guide])
			guide++;
		if (var[guide] == '=' && (exp[index][guide] == '\0'
			|| exp[index][guide] == '='))
			return (0);
		index++;
	}
	return (1);
}
/* It searches for the passed variable inside of **exp. If it finds
it, it will return 0, otherwise, it'll return 1. The function is meant
to look only for exported variables with an assignment. So if the var
doesn't contain a '=' it will return 1 even if it is technically exported. */
