/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miso_free.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jemustaj <jemustaj@student.42Porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/29 22:48:00 by jemustaj          #+#    #+#             */
/*   Updated: 2026/03/15 18:39:38 by lde-san-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/miso.h"

void	miso_reset(t_shell *miso);
void	free_token_list(t_shell *miso);
void	misoverse_free_exit(t_shell *miso, int print_err, int exit_status);
int		miso_delete_if_empty_node_str(t_shell *miso);

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
	g_signal = 0;
	return ;
}

void	free_token_list(t_shell *miso)
{
	t_token	*delete;

	while (miso->list.head != NULL)
	{
		delete = miso->list.head;
		miso->list.head = miso->list.head->next;
		if (delete->str)
			free(delete->str);
		free(delete);
	}
	miso->list.head = NULL;
	miso->list.last_node = NULL;
	return ;
}

int	miso_delete_if_empty_node_str(t_shell *miso)
{
	char	*temp;

	temp = miso->list.head->str;
	if (temp[0] == '\0')
	{
		free_token_list(miso);
		return (1);
	}
	return (0);
}
