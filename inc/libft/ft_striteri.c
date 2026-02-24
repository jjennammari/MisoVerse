/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_striteri.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-san- <lde-san-@student.42porto.co      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/19 16:05:19 by lde-san-          #+#    #+#             */
/*   Updated: 2025/04/19 16:20:12 by lde-san-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/libft.h"

void	ft_striteri(char *s, void (*f)(unsigned int, char*))
{
	unsigned int	guide;

	if (!s || !f)
		return ;
	guide = 0;
	while (s[guide])
	{
		(*f)(guide, &s[guide]);
		guide++;
	}
}
/*Applies the function ’f’ to each character of the
string passed as argument. The function takes the 
string's index as the first argument and each 
character is passed by address to ’f’ so it can be
modified if necessary */
