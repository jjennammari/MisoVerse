/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miso_redirection_utils.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-san- <lde-san-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/27 16:59:46 by lde-san-          #+#    #+#             */
/*   Updated: 2026/04/01 19:21:05 by lde-san-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/miso.h"

int		miso_no_comands(t_token *head);
int		miso_just_redirect(t_token *head);
void	miso_rderror(t_shell *miso, char *filename);

int	miso_no_comands(t_token *head)
{
	t_token	*trav;

	trav = head;
	while (trav && trav->type != PIPE)
	{
		if (trav->type == SYS_CMD || trav->type == BLT_CMD)
			return (0);
		trav = trav->next;
	}
	return (1);
}

void	miso_rderror(t_shell *miso, char *filename)
{
	write(2, ORNG, ft_strlen(ORNG));
	write(2, filename, ft_strlen(filename));
	perror(RSET": "BLOD PROMPT RSET);
	miso->list.head = miso->sgmnt;
	miso->sgmnt = NULL;
	misoverse_free_exit(miso, 0, 1);
	return ;
}

int	miso_just_redirect(t_token *head)
{
	int	exit_code;
	int	std_cpy[2];

	std_cpy[0] = dup(0);
	std_cpy[1] = dup(1);
	if (std_cpy[0] == -1 || std_cpy[1] == -1)
	{
		perror(BLOD PROMPT RSET);
		return (1);
	}
	exit_code = miso_set_channel_dad(head);
	dup2(std_cpy[0], 0);
	dup2(std_cpy[1], 1);
	close(std_cpy[0]);
	close(std_cpy[1]);
	return (exit_code);
}
