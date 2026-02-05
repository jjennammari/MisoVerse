/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-san- <lde-san-@student.42porto.co      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 17:27:54 by lde-san-          #+#    #+#             */
/*   Updated: 2025/04/16 21:53:52 by lde-san-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	guide;

	if (n == 0)
		return (0);
	guide = 0;
	while (s1[guide] && s2[guide] && s1[guide] == s2[guide] && guide < (n - 1))
		guide++;
	return (((unsigned char)s1[guide]) - ((unsigned char)s2[guide]));
}
/*compares each of the first n bytes of the s1 and s2 strings or until 
there's a character difference between the strings. It returns a positive
value if s1 is "bigger", a negative if s2 in "bigger" and 0 if they are equal*/
