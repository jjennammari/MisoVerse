/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-san- <lde-san-@student.42porto.co      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 21:17:01 by lde-san-          #+#    #+#             */
/*   Updated: 2026/02/05 22:44:30 by lde-san-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*nu_str;
	size_t	guide;
	
	if (!s1 || !s2)
		return (NULL);
	nu_str = malloc(((ft_strlen(s1)) + (ft_strlen(s2)) + 1) * sizeof (char));
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
incoming strings are NULL, it will return NULL. */
