/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-san- <lde-san-@student.42porto.co      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 18:29:10 by lde-san-          #+#    #+#             */
/*   Updated: 2025/05/05 15:41:35 by lde-san-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*allocated;
	size_t	mem_total_size;

	if (nmemb != 0 && size > (SIZE_MAX / nmemb))
		return (NULL);
	mem_total_size = nmemb * size;
	allocated = malloc(mem_total_size);
	if (!allocated)
		return (NULL);
	ft_bzero(allocated, mem_total_size);
	return (allocated);
}
/*It allocates a number of nmemb spaces of size "size" in memory as long as
the system architecture has enough space for it. Then it initializes the memory
area by filling it with null characters "\0".*/
