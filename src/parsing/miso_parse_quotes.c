/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miso_parse_quotes.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jemustaj <jemustaj@student.42Porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/14 00:51:22 by jemustaj          #+#    #+#             */
/*   Updated: 2026/03/14 03:26:07 by jemustaj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/miso.h"

int		miso_parse_quotes(t_shell *miso, t_token *node);
int		miso_validate_quotes(char *str, int *pi, int (*f)(char));
int		miso_is_squote(char c);
int		miso_is_dquote(char c);
void	miso_remove_extra_quotes(t_shell *miso);

int	miso_parse_quotes(t_shell *miso, t_token *node)
{
	char	*temp;
	int		i;

	temp = node->str;
	if (node->quotes == 1)
	{
		i = 0;
		while (temp[i])
		{
			if (miso_is_squote(temp[i]) && miso_validate_quotes(&temp[++i], &i, miso_is_squote))
				return (1);
			else if (miso_is_dquote(temp[i]) && miso_validate_quotes(&temp[++i], &i, miso_is_dquote))
				return (1);
			else if (temp[i])
				i++;
		}
	}
	return (0);
}

int	miso_validate_quotes(char *str, int *pi, int (*f)(char))
{
	int	len;

	len = 0;
	while (str[len] && !(*f)(str[len]))
		len++;
	if (!str[len])
	{
		free(str);
		racc_print(2, BLOD PROMPT MINT" Syntax error: can't find matching quote\n");
		return (1);
	}
	*pi += len;
	return (0);
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

void	miso_remove_extra_quotes(t_shell *miso)
{
	t_token	*temp;

	temp = miso->list.head;
	while (temp)
	{
		
	}
}
