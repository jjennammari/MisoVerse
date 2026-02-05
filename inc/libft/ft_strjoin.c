/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-san- <lde-san-@student.42porto.co      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 21:17:01 by lde-san-          #+#    #+#             */
/*   Updated: 2026/02/04 23:20:57 by lde-san-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	total_len;
	char	*nu_str;
	size_t	guide;

	total_len = (ft_strlen(s1) + ft_strlen(s2) + 1);
	nu_str = malloc(total_len * sizeof (char));
	if (!nu_str)
		return (NULL);
	guide = 0;
	while (s1 && *s1)
	{
		nu_str[guide] = ((char)*s1);
		guide++;
		s1++;
	}
	while (s2 && *s2)
	{
		nu_str[guide] = ((char)*s2);
		guide++;
		s2++;
	}
	nu_str[guide] = '\0';
	return (nu_str);
}
/*takes 2 strings and concatenates them into a freshly allocated 
memory area. Returns a pointer to the new string. If any of the 
incoming strings are NULL, it simply won't take part of the new
string. And if both strings are empty, it will return an empty
string. */
