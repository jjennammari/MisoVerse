/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-san- <lde-san-@student.42porto.co      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 19:52:09 by lde-san-          #+#    #+#             */
/*   Updated: 2025/04/13 12:57:33 by lde-san-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	size_t	guide;

	guide = 0;
	if (!dest && !src)
		return (NULL);
	while (guide < n)
	{
		((unsigned char *)dest)[guide] = ((unsigned char *)src)[guide];
		guide++;
	}
	return (dest);
}
/*Copies the first n bytes of the memory area pointed by src into dest. 
The memory areas must not overlap. If successful, the function returns 
dest with the memory copied*/
