/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miso_evirornment_utils.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-san- <lde-san-@student.42porto.co      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/03 14:42:57 by lde-san-          #+#    #+#             */
/*   Updated: 2026/02/03 15:46:22 by lde-san-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/miso.h"

char	**miso_envinit(char **envp)
{
	int		guide;
	char	**clone;

	guide = 0;
	while (envp[guide])
		guide++;
	clone = ft_calloc(guide + 1, sizeof(char *));
	if (!clone)
	{
		perror(BLOD"PROMPT"RSET);
		exit(1);
	}
	clone[guide] = NULL;
	while (guide-- > 0)
	{
		clone[guide] = ft_strdup(envp[guide]);
		miso_checknfree(clone[guide], NULL, NULL, clone);
	}
	return (clone);
}
/*Creates a heap-allocated replica of the **envp variable, to ensure
that its variables can be safely freed and/or modified when necessary.
It expects to be executed in the parent process, and it will exit at
any memory allocation error, terminating the shell. */

int	miso_envar_update(char **envp, char *key, char *new_value)
{
	int		guide;
	int		key_len;
	char	*old_var;

	guide = 0;
	key_len = ft_strlen(key);
	while (envp[guide] && ft_strncmp(envp[guide], key, key_len))
		guide++;
	if (!envp[guide])
		return (0);
	old_var = envp[guide];
	envp[guide] = ft_strjoin(key, new_value);
	if (envp[guide])
		free(old_var);
	else
	{
		envp[guide] = old_var;
		return (-1);
	}
	return (1);
}
/*It searches for the *key variable inside of **envp, expecting the
key formated like: "KEY_NAME=". It will then allocate a fresh string
concatenating the *key and the *new_value, and asign it to the pointer
of the old_var, freeing the old_var in the process. It will return 1
on success, 0 if the variable can't be found, and -1 on allocation
error. In case of an error, the variable won't be updated. */
