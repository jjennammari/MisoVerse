/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-san- <lde-san-@student.42porto.co      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 17:55:41 by lde-san-          #+#    #+#             */
/*   Updated: 2025/04/16 21:12:05 by lde-san-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	srclen;
	size_t	dstlen;
	size_t	guide;

	srclen = 0;
	dstlen = 0;
	guide = 0;
	while (src[srclen])
		srclen++;
	while (dst[dstlen] && dstlen < size)
		dstlen++;
	if (dstlen >= size)
		return (size + srclen);
	else
	{
		while (src[guide] && ((dstlen + guide) < size - 1))
		{
			dst[dstlen + guide] = src[guide];
			guide++;
		}
		dst[dstlen + guide] = '\0';
	}
	return (dstlen + srclen);
}
/*The function concatenates dst and src. More specifically, being src a
"Valid" C string it will put it right after the last character in dst. "dst"
is a string with some empty space and "size" is the total size of that buffer
so when we check for the lenght of dst, we are actually calculating how much 
dst is already occupied. The function returns the total size of the string
it tried to create, which in most cases will be dstlen + srclen, but it can
be (size + srclen) if there's no space in dst*/
