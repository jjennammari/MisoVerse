/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-san- <lde-san-@student.42porto.co      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 17:54:06 by lde-san-          #+#    #+#             */
/*   Updated: 2025/04/21 18:37:53 by lde-san-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/libft.h"

t_list	*ft_lstnew(void *content)
{
	t_list	*result;

	result = malloc(sizeof (t_list));
	if (!result)
		return (NULL);
	result -> content = content;
	result -> next = NULL;
	return (result);
}
/*Creates and allocates memory for a new node,
then it initializes the content of the node
with the data coming from the void pointer 
content*/
