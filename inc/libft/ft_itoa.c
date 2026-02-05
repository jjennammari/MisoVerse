/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-san- <lde-san-@student.42porto.co      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 18:41:55 by lde-san-          #+#    #+#             */
/*   Updated: 2025/04/17 19:21:16 by lde-san-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/libft.h"

static int	int_len(int n);
static void	copy_digits(int n, int size, char *str, char symbol);

char	*ft_itoa(int n)
{
	char	symbol;
	char	*result;
	int		nlen;

	if (n == -2147483648)
		return (ft_strdup("-2147483648"));
	nlen = int_len(n);
	symbol = '+';
	if (n < 0)
	{
		symbol = '-';
		n *= -1;
	}
	result = ft_calloc((nlen + 1), sizeof (char));
	if (!result)
		return (NULL);
	copy_digits(n, nlen, result, symbol);
	return (result);
}

static int	int_len(int n)
{
	if (n < 0)
		return (1 + int_len(-n));
	if (n < 10)
		return (1);
	return (1 + int_len(n / 10));
}

static void	copy_digits(int n, int size, char *str, char symbol)
{
	int	guide;

	guide = 0;
	if (symbol == '-')
		str[0] = '-';
	if (n < 10)
	{
		while (str[guide] != '\0' && guide < size)
			guide++;
		str[guide] = n + '0';
	}
	else
	{
		copy_digits(n / 10, size, str, symbol);
		copy_digits(n % 10, size, str, symbol);
	}
}
/*Takes an integer and returns a string contaning its 
character representation. It can handle any numerical 
value that can fit an int data type.*/
