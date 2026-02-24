/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-san- <lde-san-@student.42porto.co      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 19:22:41 by lde-san-          #+#    #+#             */
/*   Updated: 2025/04/19 16:03:15 by lde-san-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	unsigned int	guide;
	char			*clone;

	if (!s || !f)
		return (NULL);
	guide = 0;
	clone = ft_strdup(s);
	if (!clone)
		return (NULL);
	while (clone[guide])
	{
		clone[guide] = (*f)(guide, s[guide]);
		guide++;
	}
	return (clone);
}
/*Applies the function f to each character of the
string s, passing its index as the first argument
and the character itself as the second. A new
string is created to store the resulting string.*/
