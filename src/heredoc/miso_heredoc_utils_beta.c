/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miso_heredoc_utils_beta.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jemustaj <jemustaj@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/29 22:38:21 by jemustaj          #+#    #+#             */
/*   Updated: 2026/03/29 22:41:29 by jemustaj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/miso.h"

char	*miso_hd_check_expansion(t_shell *miso, t_token *delim, char *line);
void	miso_hd_update_nodes(t_token *hd, t_token *delim, char *file);

char	*miso_hd_check_expansion(t_shell *miso, t_token *delim, char *line)
{
	char	*res;
	int		i;

	if (delim->quotes == 1)
		return (line);
	i = 0;
	while (line[i])
	{
		if (line[i] == '$')
		{
			res = miso_hd_expand(miso, line);
			free(line);
			return (res);
		}
		i++;
	}
	return (line);
}

void	miso_hd_update_nodes(t_token *hd, t_token *delim, char *file)
{
	free(delim->str);
	hd->type = RD_IN;
	delim->str = file;
	delim->quotes = 0;
	delim->expand = 0;
}
