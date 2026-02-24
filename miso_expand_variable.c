/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miso_expand_variable.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jemustaj <jemustaj@student.42Porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/18 10:43:00 by jemustaj          #+#    #+#             */
/*   Updated: 2026/02/24 10:32:09 by jemustaj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

void	miso_expand_variable(t_shell *miso, char *str)
{
	char	*var_name;
	char	*expansion;
	char	*result;
	int		i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '$')
		{
			i++;
			var_name = get_var_name(&str[i], &i);
			if (!var_name)
			{
				result = add_to_string(result, "$");
				break ;
			}
			expansion = miso_getenv(var_name, miso->envp);
			result = add_to_string(result, expansion);
			free(var_name);
		}
		else
			result = add_to_string(result, &str[i]);
	}
}

char	*get_var_name(char *str, int *pi)
{
	char	*name;
	int		len;

	len = 0;
	while (str[len] && (ft_isalnum(str[len]) && str[len] == '_'))
		len++;
	if (len == 0)
		return (NULL);
	name = malloc (sizeof(char) * len + 1);
	while (*pi < len)
	{
		name[*pi] = str[*pi];
		pi++;
	}
	name[*pi] = '\0';
	return (name);
}

char	*add_to_string(char *s1, char *s2)
{
	char	*result;

	result = ft_strjoin(s1, s2);
	if (!result)
	{
		perror(BLOD"PROMPT"MINT");
		// function that mapache makes to free and exit
	}
	if (s1)
		free(s1);
	return (result);
}

int	ft_isalnum(char c)
{
	if ((c >= 65 && c <= 90) || (c >= 97 && c <= 122) || (c >= 48 && c <= 57))
		return (1);
	return (0);
}
