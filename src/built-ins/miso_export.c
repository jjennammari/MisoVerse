/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miso_export.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-san- <lde-san-@student.42porto.co      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/07 21:08:32 by lde-san-          #+#    #+#             */
/*   Updated: 2026/03/24 17:51:38 by lde-san-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/miso.h"

static int	miso_exparse(char *arg);
int			miso_export(t_shell *miso, char **argv);
static int	miso_parsenexport(t_shell *m, char ***env, char **argv);
static int	miso_exp_no_args(t_shell *miso, char **envp_clone, int envlen);

int	miso_export(t_shell *miso, char **argv)
{
	int		len_or_ret;
	char	**envp_clone;
	char	**og_exp;

	len_or_ret = 0;
	envp_clone = miso_matrixdup(miso->envp);
	if (!envp_clone)
		return (miso_freenret(NULL, NULL, 1, 1));
	while ((miso->envp)[len_or_ret])
		len_or_ret++;
	if (argv && argv[0] && !argv[1])
		return (miso_exp_no_args(miso, envp_clone, len_or_ret));
	og_exp = miso->exp;
	miso->exp = miso_matrixdup(og_exp);
	len_or_ret = miso_parsenexport(miso, &envp_clone, argv);
	if (len_or_ret == 2)
	{
		miso_free_matrix(envp_clone);
		miso_free_matrix(miso->exp);
		miso->exp = og_exp;
		return (1);
	}
	miso_free_matrix(miso->envp);
	miso->envp = envp_clone;
	miso_free_matrix(og_exp);
	return (len_or_ret);
}

static int	miso_exp_no_args(t_shell *miso, char **envp_clone, int envlen)
{
	if (!*(miso->envp))
	{
		miso_free_matrix(envp_clone);
		return (0);
	}
	if (!miso_export_sort(miso, envp_clone, envlen))
	{
		miso_free_matrix(envp_clone);
		return (0);
	}
	miso_free_matrix(envp_clone);
	return (1);
}

static int	miso_parsenexport(t_shell *m, char ***env, char **argv)
{
	int		guide;
	int		exit_code;
	char	*key;

	if (!m->exp)
		return (miso_freenret(NULL, NULL, 1, 2));
	guide = 1;
	exit_code = 0;
	while (argv[guide])
	{
		if (miso_exparse(argv[guide]))
		{
			exit_code = 1;
			guide++;
			continue ;
		}
		key = miso_get_key(argv[guide]);
		if (!key)
			return (miso_freenret(NULL, NULL, 1, 2));
		if (miso_exp_addorupdate(m, env, key, (argv[guide]) + ft_strlen(key)))
			return (miso_freenret(key, NULL, 1, 2));
		free(key);
		guide++;
	}
	return (exit_code);
}

static int	miso_exparse(char *arg)
{
	int	guide;
	int	print_error;

	guide = 0;
	print_error = 0;
	if (ft_isalpha(arg[guide]) || arg[guide] == '_')
	{
		while (arg[guide] && arg[guide] != '=' && (ft_isalnum(arg[guide])
				|| arg[guide] == '_'))
			guide++;
	}
	if ((arg[guide] && arg[guide] != '=') || guide == 0)
		print_error = 1;
	if (print_error)
	{
		racc_print(2, BLOD"PROMPT "MINT"export: "ORNG"`%s\':", arg);
		racc_print(2, RSET" not a valid identifier\n");
		return (1);
	}
	return (0);
}
