/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miso_heredoc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jemustaj <jemustaj@student.42Porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/04 11:47:37 by jemustaj          #+#    #+#             */
/*   Updated: 2026/03/08 18:46:08 by jemustaj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/miso.h"

int	miso_heredoc(t_shell *miso)
{
	t_token	*temp;
	int		file_nb;

	temp = miso->list.head;
	file_nb = 0;
	while (temp)
	{
		if (temp->type == HEREDOC)
		{
			file_nb += 1;
			if (miso_get_heredoc(miso, temp, file_nb))
				return (1);
		}
		temp = temp->next;
	}
	return (0);
}

int	miso_get_heredoc(t_shell *miso, t_token *hd, int file_nb)
{
	t_token	*delim;
	char	*file;
	int		fd;

	delim = hd->next;
	file = miso_hd_get_filename(file_nb);
	if (!file)
		return (1);
	if (miso_hd_open_file(file, &fd))
		return (free(file), 1);
	if (miso_hd_collect(miso, delim, fd))
		return (close(fd), free(file), 1);
	close(fd);
	miso_hd_update_nodes(hd, delim, file);
	return (0);
}

void	miso_hd_update_nodes(t_token *hd, t_token *delim, char *file)
{
	free(delim->str);
	hd->type = RD_IN;
	delim->str = file;
	delim->is_quotet = 0;
	delim->expand = 0;
}

int	miso_hd_open_file(char *file, int *fd)
{
	*fd = open(file, O_CREAT | O_WRONLY | O_TRUNC, 0600);
	if (*fd == -1)
		return (1);
	return (0);
}

char	*miso_hd_get_filename(int file_nb)
{
	char	*name;
	char	*temp;
	char	*nb;

	nb = ft_itoa(file_nb);
	if (!nb)
		return (NULL);
	temp = ft_strjoin("miso_heredoc", nb);
	free(nb);
	if (!temp)
		return (NULL);
	name = ft_strjoin(temp, ".tmp");
	free(temp);
	return (name);
}

int	miso_hd_collect(t_shell *miso, t_token *delim, int fd)
{
	char	*line;
	char	*temp;

	line = readline("> ");
	while (line)
	{
		if (miso_hd_found_delim(line, delim->str))
			break ;
		temp = miso_hd_check_expansion(miso, delim, line);
		if (!temp)
			return (free(line), 1);
		if (miso_hd_write(temp, fd))
			return (free(temp), 1);
		free(temp);
		line = readline("> ");
	}
	if (line)
		free(line);
	return (0);
}

int	miso_hd_found_delim(char *line, char *delim)
{
	size_t	len;

	len = ft_strlen(delim);
	if (ft_strncmp(line, delim, len) == 0)
		return (1);
	return (0);
}

char	*miso_hd_check_expansion(t_shell *miso, t_token *delim, char *line)
{
	char	*res;

	if (delim->is_quotet == 1)
		return (line);
	res = miso_expand_line(miso, line);
	free(line);
	return (res);
}

int	miso_hd_write(char *line, int fd)
{
	if (write(fd, line, ft_strlen(line)) == -1)
		return (1);
	if (write(fd, "\n", 1) == -1)
		return (1);
	return (0);
}
