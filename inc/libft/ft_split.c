/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-san- <lde-san-@student.42porto.co      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 20:01:53 by lde-san-          #+#    #+#             */
/*   Updated: 2025/04/16 18:39:59 by lde-san-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/libft.h"

static size_t	string_counter(char const *s, char c);
static size_t	str_len(char const *s, char c, size_t guide);
static char		**matrix_alloc(char const *s, char c, size_t str_cnt);
static size_t	len_math(char const *s, char c);

char	**ft_split(char const *s, char c)
{
	size_t	str_cnt;
	char	**godarr;
	size_t	guidea;
	size_t	guideb;

	str_cnt = string_counter(s, c);
	godarr = matrix_alloc(s, c, str_cnt);
	if (!godarr)
		return (NULL);
	guidea = 0;
	while (guidea < str_cnt)
	{
		while (*s == c && *s)
			s++;
		guideb = 0;
		while (*s != c && *s)
		{
			godarr[guidea][guideb] = *s;
			s++;
			guideb++;
		}
		godarr[guidea][guideb] = '\0';
		guidea++;
	}
	return (godarr);
}

static size_t	string_counter(char const *s, char c)
{
	size_t	guide;
	size_t	instances;
	size_t	valid;

	guide = 0;
	instances = 0;
	valid = 0;
	while (s[guide] == c && s[guide])
		guide++;
	if (!s[guide])
		return (0);
	while (s[guide])
	{
		if (s[guide] != c && valid == 0)
		{
			valid = 1;
			instances++;
		}
		else if (s[guide] == c)
			valid = 0;
		guide++;
	}
	return (instances);
}

static size_t	str_len(char const *s, char c, size_t guide)
{
	size_t	marker;
	size_t	len;
	size_t	valid;

	marker = 0;
	valid = 0;
	len = 0;
	while (*s == c && *s)
		s++;
	while (*s)
	{
		if (*s != c && valid == 0)
		{
			valid = 1;
			if (marker == guide)
			{
				return (len_math(s, c));
			}
			marker++;
		}
		else if (*s == c)
			valid = 0;
		s++;
	}
	return (len);
}

static size_t	len_math(char const *s, char c)
{
	size_t	result;

	result = 0;
	while (*s && *s != c)
	{
		s++;
		result++;
	}
	return (result);
}

static char	**matrix_alloc(char const *s, char c, size_t str_cnt)
{
	char	**main_arr;
	size_t	guide;

	main_arr = ft_calloc((str_cnt + 1), sizeof (char *));
	if (!main_arr)
		return (NULL);
	guide = 0;
	while (guide < str_cnt)
	{
		main_arr[guide] = ft_calloc((str_len(s, c, guide) + 1), sizeof (char));
		if (!main_arr[guide])
		{
			while (guide > 0)
				free(main_arr[--guide]);
			free(main_arr);
			return (NULL);
		}
		guide++;
	}
	main_arr[str_cnt] = NULL;
	return (main_arr);
}
/*Splits the string s1 on each instance of the delimiting character
"set". Allocating in the process memory for each of the resulting 
substrings and an additional NULL string, arranging all them into
a bidimensional array.*/
