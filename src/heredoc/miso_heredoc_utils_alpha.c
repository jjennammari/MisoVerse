/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miso_heredoc_utils_alpha.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jemustaj <jemustaj@student.42Porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/08 22:28:15 by jemustaj          #+#    #+#             */
/*   Updated: 2026/03/08 22:38:27 by jemustaj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/miso.h"

char	*miso_hd_get_filename(int file_nb);
int		miso_hd_open_file(char *file, int *fd);
int		miso_hd_found_delim(char *line, char *delim);
void	miso_hd_validate_delim(t_shell *miso, t_token *node);

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

int	miso_hd_open_file(char *file, int *fd)
{
	*fd = open(file, O_CREAT | O_WRONLY | O_TRUNC, 0600);
	if (*fd == -1)
		return (1);
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

void	miso_hd_validate_delim(t_shell *miso, t_token *node)
{
	char	*old;
	char	*new;

	if (node->valid_delim == 0)
		return ;
	old = node->str;
	new = ft_strdup(&old[1]);
	if (!new)
		misoverse_free_exit(miso, 1, 2);
	free(old);
	node->str = new;
}
