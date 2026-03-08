/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   misoverse_loop.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jemustaj <jemustaj@student.42Porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/29 22:48:22 by jemustaj          #+#    #+#             */
/*   Updated: 2026/03/08 21:42:38 by lde-san-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/miso.h"

void	misoverse_loop(t_shell *miso)
{
	char	*line;

	miso_init_daddy_signals;
	while (1)
	{
		miso_reset(miso);
		line = readline(PROMPT);
		if (!line)
			misoverse_free(miso, 1);
		add_history(line);
		if (miso_tokenize(miso, line))
			continue ;
		miso_print_token_list(miso);
		if (miso_parse(miso))
			continue ;
		if (miso->list.hd_count)
			if (miso_heredoc(miso))
				continue ;
		if (miso->list.hd_count && miso_handle_heredoc(miso))
			continue ;
		miso->exit_code = miso_launch(miso, miso->list.head);
	}
	return ;
}
