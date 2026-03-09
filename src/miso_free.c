/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miso_free.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jemustaj <jemustaj@student.42Porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/29 22:48:00 by jemustaj          #+#    #+#             */
/*   Updated: 2026/03/09 18:31:28 by lde-san-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/miso.h"

void	miso_reset(t_shell *miso);
void    free_token_list(t_shell *miso);
void    misoverse_free(t_shell *miso, int print_err);

void	misoverse_free(t_shell *miso, int print_err)
{
	if (print_err)
		perror(BLOD"PROMPT"RSET);
	if (miso->list.head != NULL)
		free_token_list(miso);
	miso_free_matrix(miso->envp);
	miso_free_matrix(miso->exp);
	return ;
}

void	miso_reset(t_shell *miso)
{
	if (miso->list.head != NULL)
		free_token_list(miso);
	miso->list.cmd_found = 0;
	miso->list.head = NULL;
	miso->list.hd_count = 0;
	miso->list.last_node = NULL;
	miso->node = malloc(sizeof(t_token));
	if (!miso->node)
	{
		misoverse_free(miso, 1);
		exit(1);
	}
	miso->node->expand = 0;
	miso->node->str = NULL;
	miso->node->next = NULL;
	miso->node->is_quotet = 0;
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
