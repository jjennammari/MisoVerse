/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   misoverse_loop.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jemustaj <jemustaj@student.42Porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/29 22:48:22 by jemustaj          #+#    #+#             */
/*   Updated: 2026/03/18 18:40:15 by lde-san-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/miso.h"

void		misoverse_loop(t_shell *miso);
static int	miso_process_line(t_shell *miso, char *line);
void print_envp(t_shell *miso);

void	misoverse_loop(t_shell *miso)
{
	char	*line;
	int		idle;

	line = NULL;
	idle = 1;
	while (1)
	{
		miso_reset(miso, &idle);
		miso_get_prompt(miso, &(miso->prompt));
		line = readline(miso->prompt);
		if (miso_process_line(miso, line))
			continue ;
		write(1, LIME">> "BABY, ft_strlen(LIME BABY) + 3); // Changing output color for visualizatio during testing
		idle = 0;
		miso->exit_code = miso_launch(miso, miso->list.head);
//		printf("launch passed\n\n");
	}
	return ;
}

static int	miso_process_line(t_shell *miso, char *line)
{
	if (!line)
		miso_exit(miso, NULL);
	if (!(*line))
		return (1);
	add_history(line);
	if (miso_tokenize(miso, line))
		return (1);
	printf("\ntokenization passed\n");
	miso_print_token_list(miso);
	if (miso_parse(miso))
		return (1);
	printf("parsing passed\n");	
	miso_print_token_list(miso);
	if (miso_expand(miso))
		return (1);
	printf("expansion passed\n");
	miso_print_token_list(miso);
	if (miso->list.hd_count && miso_heredoc(miso))
		return (1);
//	printf("heredoc passed\n");
//	miso_print_token_list(miso);
	return (0);
}
