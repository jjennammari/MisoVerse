/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   misoverse_loop.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jemustaj <jemustaj@student.42Porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/29 22:48:22 by jemustaj          #+#    #+#             */
/*   Updated: 2026/02/13 09:40:46 by jemustaj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

void	misoverse_loop(t_shell *miso)
{
	char	*line;

	while (1)
	{
		line = readline(PROMPT);
		if (!line)
			return ;
		add_history(line);
		miso_token_list(miso, line);
		miso_parser(miso);
		print_token_list(miso);
		misoverse_free(miso);
	}
}
