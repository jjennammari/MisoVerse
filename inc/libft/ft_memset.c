/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-san- <lde-san-@student.42porto.co      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 18:53:29 by lde-san-          #+#    #+#             */
/*   Updated: 2025/04/10 19:51:14 by lde-san-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/libft.h"

void	*ft_memset(void *s, int c, size_t n)
{
	size_t	guide;

	guide = 0;
	while (guide < n)
	{
		((unsigned char *)s)[guide] = (unsigned char)c;
		guide++;
	}
	return (s);
}
/*Initializes the first n bytes of the memory area
pointed by s, by filling it with the character c*/
