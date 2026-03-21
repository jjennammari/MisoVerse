/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   misoverse_loop.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jemustaj <jemustaj@student.42Porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/29 22:48:22 by jemustaj          #+#    #+#             */
/*   Updated: 2026/03/19 19:22:06 by lde-san-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/miso.h"

void		misoverse_loop(t_shell *miso);
static void	miso_process_signal(int *exit_code);
static int  miso_process_line(t_shell *miso, char *line);

void	misoverse_loop(t_shell *miso)
{
	char	*line;

	line = NULL;
	while (1)
	{
<<<<<<< HEAD
		miso_reset(miso);
=======
		if (line)
			free(line);
		miso_reset(miso, &idle);
>>>>>>> main
		miso_get_prompt(miso, &(miso->prompt));
		line = readline(miso->prompt);
		miso_process_signal(&miso->exit_code);
		if (miso_process_line(miso, line))
			continue ;
<<<<<<< HEAD
		write(1, LIME">> "BABY, ft_strlen(LIME BABY) + 3); // Changing output color for visualizatio during testing
		miso->exit_code = miso_launch(miso, miso->list.head);
		miso_rectify_exp(miso);
//		printf("launch passed\n\n");
=======
//		write(1, LIME">> "BABY, ft_strlen(LIME BABY) + 3); // Changing output color for visualizatio during testing
		idle = 0;
		miso->exit_code = miso_launch(miso, miso->list.head);
		printf("LAUNCH passed\n\n");
>>>>>>> main
	}
	return ;
}

static void miso_process_signal(int *exit_code)
{
	if (g_signal == SIGINT)
		*exit_code = 128 + g_signal;
	g_signal = 0;
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
	printf("\nTOKENIZATION passed\n");
	miso_print_token_list(miso);
	if (miso_parse(miso))
		return (1);
	printf("PARSING passed\n");	
	miso_print_token_list(miso);
	if (miso_expand(miso))
		return (1);
	printf("EXPANSION passed\n");
	miso_print_token_list(miso);
	if (miso->list.hd_count && miso_heredoc(miso))
		return (1);
	printf("HEREDOC passed\n");
	miso_print_token_list(miso);
	return (0);
}
