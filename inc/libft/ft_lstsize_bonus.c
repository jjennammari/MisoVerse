/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-san- <lde-san-@student.42porto.co      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 19:17:03 by lde-san-          #+#    #+#             */
/*   Updated: 2025/04/21 19:41:43 by lde-san-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/libft.h"

int	ft_lstsize(t_list *lst)
{
	int		guide;

	guide = 0;
	while (lst)
	{
		lst = lst -> next;
		guide++;
	}
	return (guide);
}
/*Calculates how many nodes are linked 
to the starting node that lst is pointing to*/
