/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   racc_print_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-san- <lde-san-@student.42porto.co      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 22:02:56 by lde-san-          #+#    #+#             */
/*   Updated: 2025/10/16 14:41:16 by lde-san-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/libft.h"

static	int	racc_strcmp(char *s, char *icon);

void	racc_putchar(int fd, char c, int *counter)
{
	int	ret;

	ret = write(fd, &c, 1);
	if (ret == 1)
		(*counter)++;
	if (ret == -1)
		*counter = -1;
}

void	racc_putstr(int fd, char *s, int mode, int *counter)
{
	if (!s)
	{
		racc_putstr(fd, "(null)", 0, counter);
		return ;
	}
	if (mode == 0)
	{
		while (*s)
			racc_putchar(fd, *s++, counter);
	}
	else
	{
		if (racc_strcmp(s, "racc"))
			(*counter) += write(fd, "\xF0\x9F\xA6\x9D", 4);
		else if (racc_strcmp(s, "yep"))
			(*counter) += write(fd, "\xE2\x9C\x85", 3);
		else if (racc_strcmp(s, "nope"))
			(*counter) += write(fd, "\xE2\x9D\x8C", 3);
		else
			racc_putstr(2, "emoji not set", 0, counter);
	}
}

static int	racc_strcmp(char *s, char *icon)
{
	size_t	guide;

	guide = 0;
	while (s[guide] && icon[guide] && s[guide] == icon[guide])
		guide++;
	if (!s[guide] && !icon[guide])
		return (1);
	return (0);
}

void	racc_putadrs(int fd, uintptr_t n, int *counter, char *base)
{
	uintptr_t	encrypter;

	encrypter = 0;
	while (base[encrypter])
		encrypter++;
	if (n >= encrypter)
	{
		racc_putadrs(fd, n / encrypter, counter, base);
		racc_putadrs(fd, n % encrypter, counter, base);
	}
	else
		racc_putchar(fd, base[n], counter);
}

void	racc_putnbs(int fd, unsigned int n, int *counter, char *base)
{
	unsigned int	encrypter;

	encrypter = 0;
	while (base[encrypter])
		encrypter++;
	if (n >= encrypter)
	{
		racc_putnbs(fd, n / encrypter, counter, base);
		racc_putnbs(fd, n % encrypter, counter, base);
	}
	else
		racc_putchar(fd, base[n], counter);
}
