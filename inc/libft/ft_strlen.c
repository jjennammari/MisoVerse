/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-san- <lde-san-@student.42porto.com     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 21:05:47 by lde-san-          #+#    #+#             */
/*   Updated: 2026/02/04 19:49:48 by lde-san-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/libft.h"

size_t	ft_strlen(const char *str)
{
	size_t	counter;

	counter = 0;
	if (!str)
		return (counter);
	while (str[counter])
		counter++;
	return (counter);
}
/*Calculates the lenght of a "Valid" C string. Excluding the \0 at the end. 
Will return 0 if str is NULL. */
