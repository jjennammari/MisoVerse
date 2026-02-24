/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-san- <lde-san-@student.42porto.co      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 16:37:00 by lde-san-          #+#    #+#             */
/*   Updated: 2025/04/22 18:17:56 by lde-san-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*head;
	t_list	*tmp;
	t_list	*guide;
	void	*nu_content;

	if (!lst || !f || !del)
		return (NULL);
	head = NULL;
	guide = lst;
	while (guide)
	{
		nu_content = f(guide -> content);
		tmp = ft_lstnew(nu_content);
		if (!tmp)
		{
			del(nu_content);
			ft_lstclear(&head, del);
			return (NULL);
		}
		ft_lstadd_back(&head, tmp);
		guide = guide -> next;
	}
	return (head);
}
/*Iterates through the nodes coming after
the one lst is pointing to (including it), using 
the function f to modify their contents in the process.
And allocates memory to create a new list filled with 
the modified versions of the nodes*/
