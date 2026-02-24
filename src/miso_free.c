/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miso_free.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jemustaj <jemustaj@student.42Porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/29 22:48:00 by jemustaj          #+#    #+#             */
/*   Updated: 2026/01/29 22:48:03 by jemustaj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

void	misoverse_free(t_shell *miso)
{
	if (miso->list.head != NULL)
		free_token_list(miso);
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
}
