/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-san- <lde-san-@student.42porto.co      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 19:31:28 by lde-san-          #+#    #+#             */
/*   Updated: 2025/04/14 20:02:13 by lde-san-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/libft.h"

char	*ft_strdup(const char *s)
{
	size_t	len;
	char	*clone;
	size_t	guide;

	len = ft_strlen(s);
	clone = malloc((len + 1) * sizeof (char));
	if (!clone)
		return (NULL);
	guide = 0;
	while (s[guide])
	{
		clone[guide] = s[guide];
		guide++;
	}
	clone[guide] = '\0';
	return (clone);
}
/*It allocates enough memory to then copy all characters from the 
string s and the null terminator into it, essentially creating a 
duplicate of said string.*/
