/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miso_prompt.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-san- <lde-san-@student.42porto.co      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/13 18:24:50 by lde-san-          #+#    #+#             */
/*   Updated: 2026/03/18 21:39:49 by lde-san-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/miso.h"

static char	*miso_prompt_cwd(t_shell *miso);
static char	*miso_prompt_sufix(char *prefix, char *cwd);
static char	*miso_prompt_prefix(t_shell *miso, char *cd);
void		miso_get_prompt(t_shell *miso, char **prompt);

void	miso_get_prompt(t_shell *miso, char **prompt)
{
	char	*cwd;
	char	*last_excd;
	char	*temp;

	cwd = miso_prompt_cwd(miso);
	miso_checknfree1d(miso, cwd, NULL, NULL);
	last_excd = ft_itoa(miso->exit_code);
	miso_checknfree1d(miso, last_excd, cwd, NULL);
	temp = miso_prompt_prefix(miso, last_excd);
	free(last_excd);
	miso_checknfree1d(miso, temp, cwd, NULL);
	if (!(*cwd))
	{
		*prompt = ft_strjoin(temp, PURP" » "RSET);
		free(temp);
		miso_checknfree1d(miso, *prompt, cwd, NULL);
		return ;
	}
	*prompt = miso_prompt_sufix(temp, cwd);
	free(cwd);
	miso_checknfree1d(miso, *prompt, temp, NULL);
	free(temp);
	return ;
}

static char	*miso_prompt_sufix(char *prefix, char *cwd)
{
	char	*temp1;
	char	*temp2;

	temp2 = NULL;
	temp1 = ft_strjoin(prefix, PINK" @ "MINT);
	if (!temp1)
		return (NULL);
	temp2 = ft_strjoin(temp1, cwd);
	free(temp1);
	if (!temp2)
		return (NULL);
	temp1 = ft_strjoin(temp2, PURP" » "RSET);
	free(temp2);
	if (!temp1)
		return (NULL);
	return (temp1);
}

static char	*miso_prompt_prefix(t_shell *miso, char *cd)
{
	char	*temp1;
	char	*temp2;

	temp1 = NULL;
	temp2 = NULL;
	if (miso->exit_code == 0)
		temp1 = ft_strdup(GOLD"["LIME"0"GOLD"] "BABY PROMPT);
	else
	{
		temp1 = ft_strjoin(BLOD"["ORNG, cd);
		if (!temp1)
			return (NULL);
		temp2 = ft_strjoin(temp1, BLOD"] "BABY PROMPT);
		free(temp1);
		if (!temp2)
			return (NULL);
		return (temp2);
	}
	if (!temp1)
		return (NULL);
	return (temp1);
}

static char	*miso_prompt_cwd(t_shell *miso)
{
	char	*pwd;
	char	*last_dir;
	int		guide;

	guide = 0;
	pwd = getcwd(NULL, 0);
	if (!pwd)
		pwd = ft_strdup("");
	miso_checknfree1d(miso, pwd, NULL, NULL);
	last_dir = pwd;
	while (pwd[guide])
	{
		if (pwd[guide] == '/')
			last_dir = pwd + guide;
		guide++;
	}
	if (last_dir && (*last_dir) == '/')
		last_dir++;
	if (!last_dir || !(*last_dir))
		last_dir = ft_strdup("");
	else
		last_dir = ft_strdup(last_dir);
	miso_checknfree1d(miso, last_dir, pwd, NULL);
	free(pwd);
	return (last_dir);
}
