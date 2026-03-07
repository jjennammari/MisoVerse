/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miso_handle_heredoc_utils.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-san- <lde-san-@student.42porto.co      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/07 20:55:49 by lde-san-          #+#    #+#             */
/*   Updated: 2026/03/07 20:55:49 by lde-san-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/miso.h"

char	*miso_hd_tmpfile(int *fd);
void	miso_hd_cleanup(int fd, char *tmp);

char	*miso_hd_tmpfile(int *fd)
{
	static int	n = 0;
	char		*num;
	char		*tmp;

	num = ft_itoa(n++);
	if (!num)
		return (NULL);
	tmp = ft_strjoin("/tmp/.miso_hd_", num);
	free(num);
	if (!tmp)
		return (NULL);
	*fd = open(tmp, O_CREAT | O_WRONLY | O_TRUNC, 0600);
	if (*fd < 0)
	{
		free(tmp);
		return (NULL);
	}
	return (tmp);
}

void	miso_hd_cleanup(int fd, char *tmp)
{
	if (fd >= 0)
		close(fd);
	if (tmp)
	{
		unlink(tmp);
		free(tmp);
	}
}
