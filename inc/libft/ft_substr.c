/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-san- <lde-san-@student.42porto.co      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 20:07:00 by lde-san-          #+#    #+#             */
/*   Updated: 2025/04/14 21:12:42 by lde-san-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	guide;
	char	*substr;
	size_t	slen;

	guide = 0;
	slen = ft_strlen(s);
	if ((size_t)start >= slen)
		return (ft_strdup(""));
	if ((slen - (size_t)start) < len)
		len = slen - (size_t)start;
	substr = malloc((len + 1) * sizeof (char));
	if (!substr)
		return (NULL);
	while (s[guide] && guide < len)
	{
		substr[guide] = s[(size_t)start + guide];
		guide++;
	}
	substr[guide] = '\0';
	return (substr);
}
/*It allocates memory and copies a substring into it. Takes the index start
at which the substring is located within s, and from there copies until the 
maximum lenght determined by len. Then ensures that the substring is null
terminated. Returns a pointed to the allocated memory or NULL if the 
allocation fails*/
