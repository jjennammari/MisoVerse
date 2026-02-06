/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miso_environment_utils_alpha.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-san- <lde-san-@student.42porto.co      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/03 14:42:57 by lde-san-          #+#    #+#             */
/*   Updated: 2026/02/06 22:11:24 by lde-san-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/miso.h"

char	**miso_envinit(char **envp);
char	*miso_getenv(const char *key, char **envp);
int		miso_add_envar(char ***envp, char *key, char *varlue);
int		miso_envar_update(char **envp, char *key, char *new_value);
char	*miso_find_envar(char **envp, const char *key, size_t klen, int *guide);

char	**miso_envinit(char **envp)
{
	int		guide;
	char	*cwd;
	char	**clone;

	guide = 0;
	while (envp[guide])
		guide++;
	clone = ft_calloc(guide + 1, sizeof(char *));
	miso_checknfree(NULL, clone, NULL, NULL);
	cwd = getcwd(NULL, 0);
	miso_checknfree(cwd, NULL, NULL, clone);
	clone[guide] = NULL;
	while (guide-- > 0)
	{
		clone[guide] = ft_strdup(envp[guide]);
		miso_checknfree(clone[guide], NULL, cwd, clone);
	}
	if ((miso_add_envar(&clone, "OLDPWD=", cwd)) == -1)
		miso_checknfree(NULL, NULL, cwd, clone);
	free(cwd);
	return (clone);
}
/*Creates a heap-allocated replica of the **envp variable, to ensure
that its variables can be safely freed and/or modified when necessary.
It expects to be executed in the parent process, and it will exit at
any memory allocation error, terminating the shell. */

int	miso_envar_update(char **envp, char *key, char *new_value)
{
	char	*old_var;
	int		guide;

	old_var = miso_find_envar(envp, key, ft_strlen(key), &guide);
	if (!old_var)
		return (1);
	if (new_value)
	{
		envp[guide] = ft_strjoin(key, new_value);
		if (envp[guide])
			return (miso_freenret(old_var, NULL, 0, 0));
		envp[guide] = old_var;
		return (-1);
	}
	while (envp[guide])
	{
		envp[guide] = envp[guide + 1];
		guide++;
	}
	return (miso_freenret(old_var, NULL, 0, 0));
}
/*It searches for the *key variable inside of **envp, expecting the
key formated like: "KEY_NAME=". Then, it will either allocate a fresh
string concatenating the *key and the *new_value, and asign it to the 
pointer of the old_var, freeing the old_var in the process. Or, if the
*new_value is set to NULL, it will shift the remaining variables in
envp, essentially removing the variable it found. The function will
return 0 on success, 1 if the variable can't be found, and -1 on allocation
error. In case of an error, the variable won't be updated. */

char	*miso_find_envar(char **envp, const char *key, size_t klen, int *guide)
{
	int	i;
	int	*index;

	if (guide)
		index = guide;
	else
		index = &i;
	*index = 0;
	while (envp[*index] && ft_strncmp(envp[*index], key, klen))
		(*index)++;
	if (!envp[*index])
		return (NULL);
	return (envp[*index]);
}
/* It searches for the *key variable inside of **envp, expecting the 
key to be formated like: "KEY_NAME=". It will then return the pointer to
the variable or NULL if it doesn't find it. As it searches the variable
it will update the index variable it received (or a local one if the 
int *guide pointer is set to NULL), so after execution, the caller will
either have the index of where the variable is in the array or the
current full length of **envp.*/

int	miso_add_envar(char ***envp, char *key, char *varlue)
{
	int		guide;
	char	**temp;

	if (miso_find_envar(*envp, key, ft_strlen(key), &guide))
		return (1);
	if (!varlue)
		return (0);
	temp = *envp;
	*envp = ft_calloc(guide + 2, sizeof(char *));
	if (*envp)
	{
		(*envp)[guide + 1] = NULL;
		(*envp)[guide] = ft_strjoin(key, varlue);
		if ((*envp)[guide])
		{
			while (guide-- > 0)
				(*envp)[guide] = temp[guide];
			free(temp);
			return (0);
		}
		free(*envp);
	}
	perror(BLOD"PROMPT"RSET);
	*envp = temp;
	return (-1);
}
/* It looks for the *key passed inside of **envp. If it finds it it'll
return 1, otherwise, it will allocate space for a new array and for the
new variable, appending it at the end. However, if *varlue is setto NULL,
it won't append anything, as it assumes that appending NULL means that
the variable is supposed to be unset, which already is if it can't be
found of course. It will return -1 on allocation error and 0 on success. */

char	*miso_getenv(const char *key, char **envp)
{
	char	*var;
	int		key_len;

	key_len = ft_strlen(key);
	if (!key || key_len == 0 || key[key_len - 1] != '=')
		return (NULL);
	var = miso_find_envar(envp, key, key_len, NULL);
	if (!var)
		return (NULL);
	return (var + key_len);
}
/* It looks at the environment variables passed on **envp, to match
the *key passed as a parameter, expecting the key formated like: 
"KEY_NAME=". Once it finds it, it returns a pointer to its value, 
or NULL if the variable doesn’t exist. The the string that's being
pointed to, is the same as the one passed around the shell, so be
concious about modifiying it, and there’s no need to free it
individually, as it will simply will be freed along with any other
allocated memory in the shell's exit sequence. */
