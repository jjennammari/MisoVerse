/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miso_environment_utils_beta.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-san- <lde-san-@student.42porto.co      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/06 22:11:44 by lde-san-          #+#    #+#             */
/*   Updated: 2026/03/02 11:20:06 by lde-san-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/miso.h"

char	*miso_get_key(char *var);
int		miso_envarcmp(const char *var, const char *key);
char	*miso_remove_envar(char **envp, const char *key);
char	*miso_extract_variable(char **envp, const char *key);
int		miso_env_addorupdate(char ***envp, char *key, char *varlue);

int	miso_env_addorupdate(char ***envp, char *key, char *varlue)
{
	int	exit_code;

	exit_code = miso_add_envar(envp, key, varlue);
	if (exit_code == -1)
		return (1);
	if (exit_code == 1)
	{
		if (key[ft_strlen(key) - 1] == '=')
		{
			if (miso_envar_update(*envp, key, varlue) == -1)
				return (1);
		}
	}
	return (0);
}
/* Attempts to both add and update the variable passed, ensuring 
that the action that's necessary is taken without the caller 
needing to worry about it. Also simplifies the return values for
these functions, making it so that it'll only return the basic 1
on error 0 on success. */

char	*miso_extract_variable(char **envp, const char *key)
{
	char	*envar;
	int		guide;
	int		key_len;

	envar = miso_remove_envar(envp, key);
	guide = 0;
	key_len = 0;
	while (envar[key_len] && envar[key_len] != '=')
		key_len++;
	if (envar[key_len] == '=')
	{
		key_len++;
		while (envar[key_len + guide])
		{
			envar[guide] = envar[key_len + guide];
			guide++;
		}
	}
	envar[guide] = '\0';
	return (envar);
}
/* Looks for the envirornment variable passed on *key. If it finds it, it
will remove the pointer from the envp array by shifting all remaining
pointers. Making the array end with 2 NULL pointers. And do a similar
treatment to the variable it found, ensuring that a string containing 
only the value of the variable is returned. Either that or it will 
return NULL if the envirorment variable can't be found. */

char	*miso_remove_envar(char **envp, const char *key)
{
	char	*envar;
	int		guide;

	envar = miso_find_envar(envp, key, &guide);
	if (!envar)
		return (NULL);
	while (envp[guide])
	{
		envp[guide] = envp[guide + 1];
		guide++;
	}
	return (envar);
}
/* Looks for the envirornment variable passed on *key. If it finds it, it
will remove the pointer from the envp array by shifting all remaining
pointers. Making the array end with 2 NULL pointers. Then it will return
to the caller a pointer to the variable it extracted. Either that or
it will return NULL if the envirorment variable can't be found. */

int	miso_envarcmp(const char *var, const char *key)
{
	int	guide;

	guide = 0;
	while (key[guide] && var[guide] && var[guide] != '=' && key[guide] != '='
		&& key[guide] == var[guide])
		guide++;
	if ((var[guide] == '\0' || var[guide] == '=')
		&& (key[guide] == '\0' || key[guide] == '='))
		return (0);
	return (1);
}
/* Compares the Key identifier with the one at the begining of
the variable passed, until either of them hits the end, a '='
or until they are diferent. If they are different it will return
1. Otherwise, it will return 0. */

char	*miso_get_key(char *var)
{
	int		guide;
	char	*key;

	guide = 0;
	while (var[guide] && var[guide] != '=')
		guide++;
	if (!var[guide])
		return (ft_strdup(var));
	key = ft_calloc(guide + 2, sizeof(char));
	if (!key)
		return (NULL);
	while (guide > -1)
	{
		key[guide] = var[guide];
		guide--;
	}
	return (key);
}
/* Makes a copy of the key coming from the envar that was passed
as a parameter. If the envar has no "key" it will simply return a
pointer to a duplicate of it. If there's an error it will return
NULL.  */
