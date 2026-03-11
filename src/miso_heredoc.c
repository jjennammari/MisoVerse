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
	miso_init_daddy_signals();
	return (0);
}

int	miso_get_heredoc(t_shell *miso, t_token *hd, int file_nb)
{
	t_token		*delim;
	char		*file;
	int			fd;
	t_sigact	old_int;
	t_sigact	old_quit;

	if (miso_hd_handle_signals(&old_int, &old_quit))
		return (1);
	delim = hd->next;
	file = miso_hd_get_filename(file_nb);
	if (!file)
		return (1);
	if (miso_hd_open_file(file, &fd))
		return (free(file), 1);//TODO: unlink if prev files
	if (miso_hd_collect(miso, delim, fd))
	{
		miso_hd_restore_signals(&old_int, &old_quit);
		unlink(file);//TODO: unlink if prev files
		return (close(fd), free(file), 1);
	}
	miso_hd_restore_signals(&old_int, &old_quit);
	close(fd);
	miso_hd_update_nodes(hd, delim, file);
	return (0);
}

int	miso_hd_collect(t_shell *miso, t_token *delim, int fd)
{
	char	*line;
	char	*temp;

	while (1)
	{
		line = readline("> ");
		if (g_signal == SIGINT)
			return (free(line), miso->exit_code = 130, 1);
		if (!line)
			return (0);//TODO: print ctrlD message & unlink prev files?
		if (miso_hd_found_delim(line, delim->str))
			break ;
		temp = miso_hd_check_expansion(miso, delim, line);
		if (!temp)
			return (free(line), 1);
		if (miso_hd_write(temp, fd))
			return (free(temp), 1);
		free(temp);
	}
	if (line)
		free(line);
	return (0);
}

int	miso_hd_write(char *line, int fd)
{
	if (write(fd, line, ft_strlen(line)) == -1)
		return (1);
	if (write(fd, "\n", 1) == -1)
		return (1);
	return (0);
}

char	*miso_hd_expand(t_shell *miso, char *line)
{
	char	*res;

	res = miso_expand(miso, line);
	if (!res)
		return (NULL);
	return (res);
}
