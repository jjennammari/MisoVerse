/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miso_free.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jemustaj <jemustaj@student.42Porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/29 22:48:00 by jemustaj          #+#    #+#             */
/*   Updated: 2026/03/19 12:23:02 by lde-san-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/miso.h"

void    miso_fdshutdown(void);
void	miso_reset(t_shell *miso);
void	free_token_list(t_shell *miso);
void	misoverse_free_exit(t_shell *miso, int print_err, int exit_status);

void	misoverse_free_exit(t_shell *miso, int print_err, int exit_status)
{
	if (print_err)
		perror(BLOD PROMPT RSET);
	if (miso->list.head != NULL)
		free_token_list(miso);
	miso_free_matrix(miso->envp);
	miso_free_matrix(miso->exp);
	free(miso->prompt);
	rl_clear_history();
	miso_fdshutdown();
	exit(exit_status & 0xFF);
	return ;
}

void	miso_reset(t_shell *miso)
{
	if (miso->prompt && *(miso->prompt))
	{
		free(miso->prompt);
		miso->prompt = NULL;
	}
	if (miso->list.head != NULL)
		free_token_list(miso);
	miso->list.cmd_found = 0;
	miso->list.head = NULL;
	miso->list.hd_count = 0;
	miso->list.last_node = NULL;
	miso->node->expand = 0;
	miso->node->str = NULL;
	miso->node->next = NULL;
	miso->node->quotes = 0;
	miso_init_daddy_signals();
	return ;
}

void	free_token_list(t_shell *miso)
{
	t_token	*temp;

	while (miso->list.head != NULL)
	{
		temp = miso->list.head;
		miso->list.head = miso->list.head->next;
		if (temp->str)
			free(temp->str);
		free(temp);
	}
	return ;
}

void    miso_fdshutdown(void)
{
	int fd;

	fd = 3;
	while (fd <= 1000)
		close(fd++);
	return ;
}
