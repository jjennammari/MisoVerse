/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoll.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-san- <lde-san-@student.42porto.co      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 20:27:18 by lde-san-          #+#    #+#             */
/*   Updated: 2026/03/07 19:37:06 by lde-san-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/libft.h"

static int	check_limits(char next_digit, long long n, int sign);

long long	ft_atoll(const char *str)
{
	size_t		guide;
	int			sign;
	long long	result;

	guide = 0;
	sign = 1;
	result = 0;
	while (str[guide] == ' ' || (str[guide] >= '\t' && str[guide] <= '\r'))
		guide++;
	if (str[guide] == '-' || str[guide] == '+')
	{
		if (str[guide] == '-')
			sign *= -1;
		guide++;
	}
	while (str[guide] >= '0' && str[guide] <= '9')
	{
		if (check_limits(str[guide], result, sign))
			return (0);
		result = result * 10 + (str[guide] - '0');
		guide++;
	}
	return (result * ((long long)sign));
}
/* Takes a string of numerical characters and returns their value 
as a long long. It ignores any leading spaces, and returns 0 if 
there are no numerical characters after the first sign is reached, 
or if the string shows a number that's bigger than LLONG_MAX or 
smaller than LLONG_MIN. */

static int	check_limits(char next_digit, long long n, int sign)
{
	int	digit;

	digit = next_digit - '0';
	if (sign == 1 && (n > (LLONG_MAX / 10)
			|| (n == (LLONG_MAX / 10) && digit > (LLONG_MAX % 10))))
		return (1);
	if (sign == -1 && (n > (LLONG_MAX / 10)
			|| (n == (LLONG_MAX / 10) && digit > ((LLONG_MAX % 10) + 1))))
		return (1);
	return (0);
}
/* Checks if by entering the next digit, the result will be a value
bigger (or smaller) than long long can handle. If it is, it'll return
1, otherwise, it'll return 0. */
