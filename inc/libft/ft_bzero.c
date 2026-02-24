/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-san- <lde-san-@student.42porto.co      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 19:30:34 by lde-san-          #+#    #+#             */
/*   Updated: 2025/04/12 22:29:28 by lde-san-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/libft.h"

void	ft_bzero(void *s, size_t n)
{
	size_t	guide;

	guide = 0;
	while (guide < n)
	{
		((unsigned char *)s)[guide] = '\0';
		guide++;
	}
}
/*Fills up the first n bytes of the memory pointed
by s, with null characters \0. It may write or overwrite the memory*/
