/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miso_tokenization_quotes.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jemustaj <jemustaj@student.42Porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/19 22:10:36 by jemustaj          #+#    #+#             */
/*   Updated: 2026/02/24 10:39:47 by jemustaj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/miso.h"

int	miso_add_quotes(t_shell *miso, char *str, int *pi, int (*f)(char))
{
	int		len;
	char	*temp;

	miso->node->expand = 0;
	miso->node->is_quotet = 1;
	len = miso_validate_quotes(miso, str, f);
	if (len == -1)
		return (1);
	*pi += len + 1;
	if (len == 0)
		return (0);
	temp = miso_create_token_str(str, len);
	miso_add_to_list(miso, temp, ARG);
	return (0);
}

int	miso_validate_quotes(t_shell *miso, const char *str, int (*f)(char))
{
	int	len;

	len = 0;
	while (str[len] && !(*f)(str[len]))
	{
		if (str[len] == '$')
			miso->node->expand = 1;
		len++;
	}
	if (!str[len])
	{
		racc_print(2, BLOD"PROMPT"MINT" Syntax error: can't find matching quote\n");
		return (-1);
	}
	else if (str[len] != '"' && miso->node->expand == 1)
		miso->node->expand = 0;
	return (len);
}

int	miso_is_squote(char c)
{
	if (c == '\'')
		return (1);
	return (0);
}

int	miso_is_dquote(char c)
{
	if (c == '"')
		return (1);
	return (0);
}
