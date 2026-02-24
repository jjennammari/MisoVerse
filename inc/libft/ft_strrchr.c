/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-san- <lde-san-@student.42porto.co      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 21:19:17 by lde-san-          #+#    #+#             */
/*   Updated: 2025/04/13 13:13:18 by lde-san-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int	slen;

	slen = 0;
	while (s[slen])
		slen++;
	while (slen >= 0 && s[slen] != (unsigned char)c)
		slen--;
	if (s[slen] == (unsigned char)c)
		return ((char *)&s[slen]);
	return (NULL);
}
/*Looks for the last instance of the character c in the "Valid" string s and
returns a pointer to its memory address, or NULL if it doesn't find it.*/
