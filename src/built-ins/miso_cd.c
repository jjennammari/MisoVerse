/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miso_cd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-san- <lde-san-@student.42porto.co      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/03 13:25:13 by lde-san-          #+#    #+#             */
/*   Updated: 2026/02/04 18:01:55 by lde-san-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/miso.h"

int miso_cd(t_shell *miso, char **cmd)
{
	int	arc;
	char 

	arc = 0;
	while (cmd[arc])
		arc++;
	if (arc == 2)
		return (miso_chdir_to_arg(miso, cmd[1], ft_strlen(cmd[1])));
	if (arc == 1)
		return (miso_chdir_to_home(miso, cmd[1], ft_strlen(cmd[1])));
	racc_print(2, BLOD"PROMPT "MINT"cd: "ORNG"too many arguments\n"RSET);
	return (1);
}
