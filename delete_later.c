/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delete_later.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jemustaj <jemustaj@student.42Porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/29 22:50:38 by jemustaj          #+#    #+#             */
/*   Updated: 2026/02/18 21:53:55 by jemustaj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/miso.h"

void	miso_print_token_list(t_shell *miso)
{
	t_token	*temp;
	int		t_count;

	temp = miso->list.head;
	t_count = 0;
	while (temp)
	{
		printf("Token %d\n", t_count);
		printf("Token STR: %s\n", temp->str);
		printf("Token TYPE: %d\n", temp->type);
		printf("Expandable: %d\n\n", temp->expand);
		temp = temp->next;
		t_count += 1;
	}
}
