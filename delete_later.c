/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delete_later.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jemustaj <jemustaj@student.42Porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/29 22:50:38 by jemustaj          #+#    #+#             */
/*   Updated: 2026/01/29 22:50:40 by jemustaj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

void	print_token_list(t_shell *miso)
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
		printf("Expandable: %s\n\n", temp->expand?"true":"false");
		temp = temp->next;
		t_count += 1;
	}
}
