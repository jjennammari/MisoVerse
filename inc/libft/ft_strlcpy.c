/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-san- <lde-san-@student.42porto.co      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 21:21:26 by lde-san-          #+#    #+#             */
/*   Updated: 2025/04/14 20:05:26 by lde-san-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	size_t	srclen;
	size_t	guide;

	srclen = 0;
	guide = 0;
	while (src[srclen])
		srclen++;
	if (size != 0)
	{
		while (src[guide] && guide < size - 1)
		{
			dst[guide] = src[guide];
			guide++;
		}
		dst[guide] = '\0';
	}
	return (srclen);
}
/*copies the characters from src to dest up to (size - 1). This ensures
that the string can then be null terminated. The function returns the
lenght of the string that it tried to create, which is the lenght of src
in this case.*/
