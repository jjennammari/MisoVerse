/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-san- <lde-san-@student.42porto.co      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 21:17:01 by lde-san-          #+#    #+#             */
/*   Updated: 2025/04/15 15:44:02 by lde-san-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	total_len;
	char	*nu_str;
	size_t	guidea;
	size_t	guideb;

	total_len = (ft_strlen(s1) + ft_strlen(s2) + 1);
	nu_str = malloc(total_len * sizeof (char));
	if (!nu_str)
		return (NULL);
	guidea = 0;
	while (s1[guidea])
	{
		nu_str[guidea] = ((char *)s1)[guidea];
		guidea++;
	}
	guideb = 0;
	while (s2[guideb])
	{
		nu_str[guidea + guideb] = ((char *)s2)[guideb];
		guideb++;
	}
	nu_str[guidea + guideb] = '\0';
	return (nu_str);
}
/*takes 2 strings and concatenates them into a freshly allocated 
memory area. Returns a pointer to the new string*/
