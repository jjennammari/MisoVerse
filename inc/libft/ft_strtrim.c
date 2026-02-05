/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-san- <lde-san-@student.42porto.co      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 17:51:28 by lde-san-          #+#    #+#             */
/*   Updated: 2025/04/17 18:51:08 by lde-san-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	char			*end;
	unsigned int	start;

	if (!s1 || !set)
		return (NULL);
	start = 0;
	while (ft_strchr(set, s1[start]) && s1[start])
		start++;
	if (!s1[start])
	{
		end = ft_calloc(1, sizeof (char));
		if (!end)
			return (NULL);
		return (end);
	}
	end = (char *)(s1 + ft_strlen(s1));
	while (ft_strchr(set, *end))
		end--;
	return (ft_substr(s1, start, ((size_t)end - (size_t) & s1[start]) + 1));
}
/*Trims away the leading and tailing characters "set" from the original
string s1 and allocates memory to paste the remaining substring into it*/
