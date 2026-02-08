/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miso_export_sort.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-san- <lde-san-@student.42porto.co      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/07 21:35:07 by lde-san-          #+#    #+#             */
/*   Updated: 2026/02/07 23:59:22 by lde-san-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/miso.h"

int	miso_export_sort(char **envp, int envp_c)
{
	char	*tiny;
	int		guide;
	int		tiny_len;

	if (!envp || !(*envp))
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
		if (miso_printnfree(envp, tiny, tiny_len))
			return (miso_free_matrix(envp), 1);
	}
	return (free(envp), 0);
}
/* Remember that a NULL envp, when export gets called alone, returns
0 and prints nothing. In this case we are only returning 1 because it
would mean an allocation error in this case, since we are planning to
call this function with a duplicate of envp. */

int	miso_printnfree(char **envp, char *tiny, int tiny_len)
{
	char	*key;
	int		key_len;
	int		guide;
	char	*var;

	key_len = 0;
	while (tiny[key_len] && tiny[key_len] != '=')
		key_len++;
	if (!tiny[key_len])
		var = miso_remove_envar(envp, tiny, tiny_len);
	else
	{
		key = ft_calloc(key_len + 2, sizeof(char));
		if (!key)
			return (1);
		guide = 0;
		while (guide < (key_len + 1))
			key[guide] = tiny[guide++];
		var = miso_remove_envar(envp, key, key_len + 1);
		free(key);
	}
	racc_print(1, LIME"declare -x"NEOR"%s\n", var);
	free(var);
	return (0);
}
