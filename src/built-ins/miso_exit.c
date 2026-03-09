/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miso_exit.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-san- <lde-san-@student.42porto.co      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/04 20:18:31 by lde-san-          #+#    #+#             */
/*   Updated: 2026/03/08 22:29:09 by lde-san-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/miso.h"

static int	miso_exit_iszero(char *arg, int *i);
int			miso_exit(t_shell *miso, char **argv);
static void	miso_exit_notnum(t_shell *miso, char **argv);
static int	miso_exit_yesnum(char *arg, long long *exit_cd);

int	miso_exit(t_shell *miso, char **argv)
{
	long long	exit_cd;

	if (!argv[1])
	{
		miso_free_matrix(argv);
		misoverse_free(miso, 0);
		exit(miso->exit_code % 256);
	}
	if (miso_exit_yesnum(argv[1], &exit_cd))
	{
		if (argv[2])
		{
			racc_print(2, ORNG"exit\n"RSET);
			racc_print(2, BLOD"PROMPT "MINT"exit: "RSET"too many arguments\n");
			return (1);
		}
		racc_print(1, MINT"exit\n"RSET);
		miso_free_matrix(argv);
		misoverse_free(miso, 0);
		exit(exit_cd % 256);
	}
	miso_exit_notnum(miso, argv);
	return (1);
}

static int	miso_exit_yesnum(char *arg, long long *exit_cd)
{
	int	i;

	if (!arg || !arg[0])
		return (0);
	if (miso_exit_iszero(arg, &i))
	{
		*exit_cd = 0;
		return (1);
	}
	if (arg[i] == 45 || arg[i] == 43)
		i++;
	if (!arg[i] || !ft_isdigit(arg[i]))
		return (0);
	while (arg[i])
	{
		if (!ft_isdigit(arg[i]))
			return (0);
		i++;
	}
	*exit_cd = ft_atoll(arg);
	if (!(*exit_cd))
		return (0);
	return (1);
}

static int	miso_exit_iszero(char *arg, int *i)
{
	int		guide;

	*i = 0;
	while (arg[*i] && (arg[*i] == 32 || (arg[*i] >= 9 && arg[*i] <= 13)))
		(*i)++;
	guide = *i;
	if (arg[guide] == 45 || arg[guide] == 43)
		guide++;
	while (arg[guide] == '0')
		guide++;
	if (arg[guide])
		return (0);
	return (1);
}

static void	miso_exit_notnum(t_shell *miso, char **argv)
{
	racc_print(2, ORNG"exit\n"RSET);
	racc_print(2, BLOD"PROMPT "MINT"exit: "BABY"%s"RSET, argv[1]);
	racc_print(2, ": numeric argument required\n");
	miso_free_matrix(argv);
	misoverse_free(miso, 0);
	exit(2);
}
