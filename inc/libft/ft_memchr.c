/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-san- <lde-san-@student.42porto.co      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 12:02:28 by lde-san-          #+#    #+#             */
/*   Updated: 2025/04/13 12:34:06 by lde-san-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t	guide;

	guide = 0;
	while (guide < n)
	{
		if (((unsigned char *)s)[guide] == (unsigned char)c)
			return ((void *)&(((unsigned char *)s)[guide]));
		guide++;
	}
	return (NULL);
}
/*It looks for the character c in the first n bytes of s. It returns a pointer
to the address of the character or NULL if it doesn't find it*/
