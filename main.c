/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jemustaj <jemustaj@student.42Porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/29 22:47:52 by jemustaj          #+#    #+#             */
/*   Updated: 2026/02/13 15:03:10 by jemustaj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	main(void)
{
	t_shell	miso;

	init_variables(&miso);
	misoverse_loop(&miso);
	return (0);
}

void	init_variables(t_shell *miso)
{
	miso->exit_code = 0;
	miso->node = malloc(sizeof(t_token));
	if (!miso->node)
		return ;
	miso->node->expand = 0;
	miso->node->str = NULL;
	miso->node->next = NULL;
	miso->list.cmd_found = 0;
	miso->list.head = NULL;
	miso->list.last_node = NULL;
}
