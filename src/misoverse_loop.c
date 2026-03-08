/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   misoverse_loop.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jemustaj <jemustaj@student.42Porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/29 22:48:22 by jemustaj          #+#    #+#             */
/*   Updated: 2026/03/04 19:25:41 by jemustaj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/miso.h"

void	misoverse_loop(t_shell *miso)
{
	char	*line;

	while (1)
	{
		line = readline(PROMPT);
		if (!line)
		{
			perror(BLOD"PROMPT"MINT);
			// function that mapache makes to free and exit
		}
		add_history(line);
		if (miso_tokenize(miso, line))
			continue ;
		miso_print_token_list(miso);
		if (miso_parse(miso))
			continue ;
		if (miso->list.hd_count)
			if (miso_heredoc(miso))
				continue ;
	}
}
