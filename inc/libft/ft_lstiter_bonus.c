/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstiter.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-san- <lde-san-@student.42porto.co      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 16:30:05 by lde-san-          #+#    #+#             */
/*   Updated: 2025/04/22 16:34:04 by lde-san-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/libft.h"

void	ft_lstiter(t_list *lst, void (*f)(void *))
{
	t_list	*guide;

	guide = lst;
	while (guide)
	{
		f(guide -> content);
		guide = guide -> next;
	}
}
/*Iterates through the nodes coming after
the one lst is pointing to (including it), using 
the function f to modify their contents in the process*/
