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

#include "../inc/miso.h"

void	miso_expand_variable(t_shell *miso, char *str, t_token *node)
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
			var_name = miso_get_var_name(&str[i], &i);
			if (!var_name)
			{
				result = miso_add_to_string(result, "$");
				break ;
			}
			expansion = miso_getenv(var_name, miso->envp);
			result = miso_add_to_string(result, expansion);
			free(var_name);
		}
		else
		{
			result = miso_add_to_string(result, &str[i]);
			i++;
		}
	}
	miso_add_new_token_str(result, node);
}

void	miso_add_new_token_str(char *str, t_token *node)
{
	free(node->str);
	node->str = str;
	node->expand = 0;
}

char	*miso_get_var_name(char *str, int *pi)
{
	char	*name;
	int		len;

	len = 0;
	while (str[len] && (miso_is_alnum(str[len]) && str[len] == '_'))
		len++;
	if (len == 0)
		return (NULL);
	name = malloc(sizeof(char) * len + 1);
	if (!name)
	{
		perror(BLOD"PROMPT"MINT");
		// function that mapache makes to free and exit
	}
	while (*pi < len)
	{
		name[*pi] = str[*pi];
		pi++;
	}
	name[*pi] = '\0';
	return (name);
}

char	*miso_add_to_string(char *s1, char *s2)
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

int	miso_is_alnum(char c)
{
	if ((c >= 65 && c <= 90) || (c >= 97 && c <= 122) || (c >= 48 && c <= 57))
		return (1);
	return (0);
}
