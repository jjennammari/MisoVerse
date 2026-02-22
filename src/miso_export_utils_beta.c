/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miso_export_utils_beta.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-san- <lde-san-@student.42porto.co      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/07 21:35:07 by lde-san-          #+#    #+#             */
/*   Updated: 2026/02/22 11:47:34 by lde-san-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/miso.h"

static void	miso_export_print_format(char *var);
void		miso_envp_exp_filter(char **exp, char **envp);
static int	miso_printnfree(char **exp, char **envp, char *tiny);
int			miso_export_sort(t_shell *miso, char **envp, int envp_c);

int	miso_export_sort(t_shell *miso, char **envp, int envp_c)
{
	char	*tiny;
	int		guide;
	int		tiny_len;

	if (!envp)
		return (miso_freenret(NULL, NULL, 1, 1));
	while (envp_c-- > 0)
	{
		guide = 0;
		tiny = envp[guide];
		tiny_len = ft_strlen(tiny);
		while (envp[guide])
		{
			if (ft_strncmp(tiny, envp[guide], tiny_len + 1) > 0)
			{
				tiny = envp[guide];
				tiny_len = ft_strlen(tiny);
			}
			guide++;
		}
		if (miso_printnfree(miso->exp, envp, tiny, tiny_len))
			return (miso_free_matrix(envp), 1);
	}
	return (free(envp), 0);
}
/* When export gets called on its own, it prints the whole envp 
in alphabetical order. This function searches for the "smallest"
envar one by one, extracts it from the envp, prints it and frees 
it. Making it so that the envp gets gradually smaller. The function
expects to be called with a duplicate of the envp array so these
actions don't really affect the shell state. A NULL envp, when 
export gets called alone, returns 0 and prints nothing. In this 
case we are only returning 1 in that situation because it would 
mean an allocation error in this case, since we are planning to
call this function with a duplicate of envp. */

static int	miso_printnfree(char **exp, char **envp, char *tiny)
{
	char	*key;
	char	*var;

	key = miso_get_key(tiny);
	if (!key)
		return (1);
	var = miso_remove_envar(envp, key);
	if (miso_expcheck(exp, key, NULL))
		miso_export_print_format(var);
	return (miso_freenret(key, var, 0, 0));
}
/* Separates the "KEY=" from the "variable" in the envar, in
order to search for it in envp  and extract it. Then, if it 
is exported, the envar is printed in the expected format for 
export, and freed. */

static void	miso_export_print_format(char *var)
{
	char	*writer;

	writer = var;
	while (*writer && *writer != '=')
		writer++;
	if (*writer == '=')
	{
		writer = var;
		racc_print(1, LIME"declare -x ");
		while (*writer && *writer != '=')
			racc_print(1, PURP"%c", writer++);
		racc_print(1, BABY"%c", writer++);
		racc_print(1, MINT"\"");
		while (*writer)
			racc_print(1, ORNG"%c", writer++);
		racc_print(1, MINT"\""RSET"\n");
	}
	else
		racc_print(1, LIME"declare -x "PURP"%s\n", var);
	return ;
}
/* Prints the variable "var" in the format that's expected
when calling export alone (declare -x KEY="Value")  */

void	miso_exp_filter(char **exp, char **envp)
{
	int		guide;
	char	*not_exported;

	guide = 0;
	while (*envp)
	{
		guide = 0;
		if (!miso_isvarinexp(exp, *envp))
		{
			envp++;
			continue ;
		}
		not_exported = *envp;
		while (envp[guide])
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
