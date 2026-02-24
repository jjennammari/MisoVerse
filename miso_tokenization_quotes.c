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

#include "parsing.h"

void	add_quotes(t_shell *miso, char *str, int *pi, int (*f)(char))
{
	int		len;
	char	*temp;

	miso->node->expand = 0;
	len = validate_quotes(miso, str, f);
	if (len == -1)
		return ;
	*pi += len + 1;
	if (len == 0)
		return ;
	temp = create_token_str(str, len);
	add_to_list(miso, temp, ARG);
}

int	validate_quotes(t_shell *miso, const char *str, int (*f)(char))
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
		miso->list.syntax_err = 1;
		racc_print(2, BLOD"PROMPT"MINT" Syntax error: can't find matching quote\n");
		return (-1);
	}
	if (str[len] != '"' && miso->node->expand == 1)
		miso->node->expand = 0;
	return (len);
}

int	is_squote(char c)
{
	if (c == '\'')
		return (1);
	return (0);
}

int	is_dquote(char c)
{
	if (c == '"')
		return (1);
	return (0);
}
