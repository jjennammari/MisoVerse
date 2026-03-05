/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miso_exit.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-san- <lde-san-@student.42porto.co      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/04 20:18:31 by lde-san-          #+#    #+#             */
/*   Updated: 2026/03/04 20:40:30 by lde-san-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/miso.h"

static int	check_limits(char *str, long long nbr)
{
	char	*llongmax;
	char	*llongmin;
	size_t	arg_len;

	llongmax = "9223372036854775807";
	llongmin = "-9223372036854775808";
	arg_len = ft_strlen(str);
	if (nbr > LLONG_MAX || nbr < LLONG_MIN)
		return (0);
	if (nbr == LLONG_MAX && ft_strncmp(str, llongmax, arg_len))
		return (0);
	if (nbr == LLONG_MIN && ft_strncmp(str, llongmin, arg_len))
		return (0);
	return (1);
}

static int	is_numeric(char *str)
{
	int			guide;
	long long	number;

	if (!str)
		return (0);
	guide = 0;
	number = racc_atoll(str);
	if (!check_limits(str, number))
		return (0);
	while (str[guide] == ' ')
		guide++;
	if (str[guide] && (str[guide] == '+' || str[guide] == '-'))
		guide++;
	while (str[guide])
	{
		if (str[guide] < 48 || str[guide] > 57)
			return (0);
		guide++;
	}
	return (1);
}

static void	is_not_numeric(t_shell *miso, char *str)
{
	racc_print(2, BLOD"PROMPT "MINT"exit: "BABY"%s"RSET, str);
	racc_print(2, ": numeric argument required\n");
	misoverse_free(miso);
	exit(2);
}

static void	exit_success(t_shell *miso, t_exec	*exec_node)
{
	long long	exit_cd;

	exit_cd = ft_atoll(exec_node->argv[1]);
	if (exec_node->argv[2])
	{
		racc_print(2, BLOD"PROMPT "MINT"exit: "RSET"too many arguments\n");
		misoverse_free(miso);
		exit(1);
	}
	racc_print(1, MINT"exit");
	misoverse_free(miso);
	exit((unsigned char)exit_cd);
}

void	ft_exit(t_shell *shell, t_exec *exec_node, t_fork *fork)
{
	if (!exec_node->argv[1])
		return ;
	if (is_numeric(exec_node->argv[1]))
		exit_success(shell, exec_node, fork);
	else
		is_not_numeric(shell, exec_node, fork);
}
