/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   racc_print.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-san- <lde-san-@student.42porto.co      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 22:00:55 by lde-san-          #+#    #+#             */
/*   Updated: 2025/10/16 14:40:47 by lde-san-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/libft.h"

static unsigned int	vibechek(int fd, int n, int *counter);
static void			ptr(int fd, va_list arg, int *counter);
static void			racc_format_check(int fd, va_list arg, char c, int *cnt);

int	racc_print(int fd, const char *format, ...)
{
	va_list	arg;
	int		counter;

	va_start(arg, format);
	counter = 0;
	while (*format)
	{
		if (*format == '%')
			racc_format_check(fd, arg, *(++format), &counter);
		else
			racc_putchar(fd, *format, &counter);
		format++;
		if (counter == -1)
			break ;
	}
	va_end(arg);
	return (counter);
}

static void	racc_format_check(int fd, va_list arg, char c, int *cnt)
{
	if (c == '%')
		racc_putchar(fd, '%', cnt);
	else if (c == 'c')
		racc_putchar(fd, va_arg(arg, int), cnt);
	else if (c == 's')
		racc_putstr(fd, va_arg(arg, char *), 0, cnt);
	else if (c == 'e')
		racc_putstr(fd, va_arg(arg, char *), 1, cnt);
	else if (c == 'p')
		ptr(fd, arg, cnt);
	else if (c == 'i' || c == 'd')
		racc_putnbs(fd, vibechek(fd, va_arg(arg, int), cnt), cnt, "0123456789");
	else if (c == 'u')
		racc_putnbs(fd, va_arg(arg, unsigned int), cnt, "0123456789");
	else if (c == 'x')
		racc_putnbs(fd, va_arg(arg, unsigned int), cnt, "0123456789abcdef");
	else if (c == 'X')
		racc_putnbs(fd, va_arg(arg, unsigned int), cnt, "0123456789ABCDEF");
	return ;
}

static unsigned int	vibechek(int fd, int n, int *counter)
{
	if (n < 0)
	{
		racc_putchar(fd, '-', counter);
		return ((unsigned int)(-n));
	}
	return ((unsigned int)n);
}

static void	ptr(int fd, va_list arg, int *counter)
{
	uintptr_t	address;

	address = (uintptr_t)(va_arg(arg, void *));
	if (address == 0)
	{
		racc_putstr(fd, "(nil)", 0, counter);
		return ;
	}
	racc_putstr(fd, "0x", 0, counter);
	racc_putadrs(fd, address, counter, "0123456789abcdef");
}
/*This modfied version of the printf function, has fewer functionalities in
regards  to  formatting  options, but adds the option to print to different 
file descriptors, and the %e format specifier. Who's sole purpose is to hard
code a couple emojis that may add readability when testing code. These emojis
may be called by adding the strings "racc", "yes" and "nope" respectively*/
