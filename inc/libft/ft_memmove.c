/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-san- <lde-san-@student.42porto.co      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 20:13:47 by lde-san-          #+#    #+#             */
/*   Updated: 2025/05/06 17:10:23 by lde-san-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	size_t	guide;

	if ((uintptr_t)src == (uintptr_t)dest)
		return (dest);
	else if ((uintptr_t)src < (uintptr_t)dest)
	{
		guide = n;
		while (guide > 0)
		{
			guide--;
			((unsigned char *)dest)[guide] = ((unsigned char *)src)[guide];
		}
	}
	else
	{
		guide = 0;
		while (guide < n)
		{
			((unsigned char *)dest)[guide] = ((unsigned char *)src)[guide];
			guide++;
		}
	}
	return (dest);
}
/*Copies the first n bytes of the memory area pointed by src into dest. 
The memory areas may overlap. If successful, the function returns dest 
with the memory copied. The use of the uintptr_t ensures that the 
comparison is done between unsigned ints, securing that the function 
properly determines whether src is ahead, or behind dest with the "=="
"<" operands, which would otherwise not be possible with void pointers.*/
