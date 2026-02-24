/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-san- <lde-san-@student.42porto.co      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 22:38:33 by lde-san-          #+#    #+#             */
/*   Updated: 2025/06/03 12:25:07 by lde-san-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/get_next_line_bonus.h"

t_lst	*racc_lstnew(char c)
{
	t_lst	*result;

	result = malloc(sizeof (t_lst));
	if (!result)
		return (NULL);
	result -> letter = c;
	result -> next = NULL;
	result -> tail = NULL;
	return (result);
}

size_t	racc_linesize(t_lst *lst)
{
	size_t	count;

	count = 0;
	while (lst)
	{
		count++;
		if (lst -> letter == '\n')
			break ;
		lst = lst -> next;
	}
	return (count);
}

int	racc_findend(t_lst **lst)
{
	t_lst	*traveler;

	if (!*lst)
		return (-1);
	traveler = *lst;
	while (traveler)
	{
		if (traveler -> letter == '\n')
			return (0);
		traveler = traveler -> next;
	}
	return (-1);
}

void	racc_delnode(t_lst **lst, int clear_all)
{
	t_lst	*temp;

	temp = NULL;
	while (*lst)
	{
		temp = (*lst)-> next;
		free(*lst);
		*lst = temp;
		if (clear_all == 0)
			return ;
	}
	*lst = NULL;
	return ;
}

int	racc_lstadd(t_lst **lst, t_lst *new)
{
	t_lst	*last;

	if (!lst || !new)
		return (-1);
	if (!*lst)
	{
		*lst = new;
		(*lst)-> tail = new;
		return (0);
	}
	if (!(*lst)->tail)
	{
		last = *lst;
		while (last)
		{
			if (!(last -> next))
				break ;
			last = last -> next;
		}
		(*lst)-> tail = last;
	}
	(*lst)-> tail -> next = new;
	(*lst)-> tail = new;
	return (0);
}
