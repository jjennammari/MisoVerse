/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miso_context.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-san- <lde-san-@student.42porto.co      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/18 18:56:42 by lde-san-          #+#    #+#             */
/*   Updated: 2026/03/18 21:37:09 by lde-san-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/miso.h"

int			miso_context(t_shell *miso, char **argv);
static void	miso_load_buff(char *buffer, char *str);
static void	miso_print_out_of_context(t_shell *m, char *b);
static int	miso_print_context(char *exp, char *env, char *high, char *b);

int	miso_context(t_shell *miso, char **argv)
{
	int		guide;
	int		i;
	char	b[70];

	i = 0;
	ft_memset(b, '\0', 70);
	racc_print(1, MINT"\nExport Summary: \n"RSET);
	while (miso->exp[i])
	{
		guide = 0;
		while (miso->envp[guide])
		{
			if (miso_print_context(miso->exp[i], miso->envp[guide], argv[1], b))
				break ;
			guide++;
		}
		if (!miso->envp[guide])
			printf(BLOD">> "NEOR"%s\n"RSET, miso->exp[i]);
		i++;
	}
	racc_print(1, MINT"\nNon Exported: \n"RSET);
	miso_print_out_of_context(miso, b);
	return (0);
}

static void	miso_load_buff(char *buffer, char *str)
{
	int	i;

	i = 0;
	while (i < 69)
	{
		if (*str)
		{
			buffer[i] = *str;
			str++;
		}
		else
			buffer[i] = '\0';
		i++;
	}
	return ;
}

static void	miso_print_out_of_context(t_shell *m, char *b)
{
	int	guide;

	guide = 0;
	while (m->envp[guide])
	{
		if (miso_isvarinexp(m->exp, m->envp[guide]))
		{
			miso_load_buff(b, m->envp[guide]);
			racc_print(1, GOLD" >> "PINK"%s", b);
			if (ft_strlen(m->envp[guide]) > 69)
				racc_print(1, GOLD"...\n"RSET);
			else
				racc_print(1, "\n"RSET);
		}
		guide++;
	}
	return ;
}

static int	miso_print_context(char *exp, char *env, char *high, char *b)
{
	int	varlen;

	varlen = ft_strlen(env);
	if (ft_strnstr(env, exp, varlen))
	{
		miso_load_buff(b, env);
		if (high && ft_strnstr(env, high, varlen))
			racc_print(1, MINT"  >> "BABY"%s", b);
		else
			racc_print(1, PURP"  >> "RSET"%s", b);
		if (varlen > 69)
			racc_print(1, GOLD"...\n"RSET);
		else
			racc_print(1, "\n"RSET);
		return (1);
	}
	return (0);
}
