/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   misoverse_loop.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jemustaj <jemustaj@student.42Porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/29 22:48:22 by jemustaj          #+#    #+#             */
/*   Updated: 2026/02/20 21:31:52 by jemustaj         ###   ########.fr       */
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
			break ;
		}
		add_history(line);
		if (miso_tokenization(miso, line))
			continue ;
		if (miso_parser(miso))
			continue ;
	}
}
