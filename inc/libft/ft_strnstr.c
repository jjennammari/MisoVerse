/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-san- <lde-san-@student.42porto.co      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 17:32:21 by lde-san-          #+#    #+#             */
/*   Updated: 2025/04/14 18:20:41 by lde-san-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	guidea;
	size_t	guideb;
	char	*start_little;

	guidea = 0;
	if (!little[guidea])
		return ((char *)big);
	while (big[guidea] && guidea < len)
	{
		guideb = 0;
		if (big[guidea] == little[guideb])
		{
			start_little = &((char *)big)[guidea];
			while (little[guideb] && (guidea + guideb) < len
				&& big[guidea + guideb] == little[guideb])
				guideb++;
			if (!little[guideb])
				return (start_little);
		}
		guidea++;
	}
	return (NULL);
}
/*Searches into the first len characters of the string big for the 
string little, then it returns a pointer to the start of little or
NULL if it doesn't find it.*/
