/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miso_heredoc_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jemustaj <jemustaj@student.42Porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/08 22:28:15 by jemustaj          #+#    #+#             */
/*   Updated: 2026/03/08 22:38:27 by jemustaj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/miso.h"

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

char	*miso_hd_check_expansion(t_shell *miso, t_token *delim, char *line)
{
	char	*res;
	int		i;

	if (delim->is_quotet == 1)
		return (line);
	i = 0;
	while (line[i])
	{
		if (line[i] == '$')
		{
			res = miso_hd_expand(miso, line);
			free(line);
			return (res);
		}
		i++;
	}
	return (line);
}

void	miso_hd_update_nodes(t_token *hd, t_token *delim, char *file)
{
	free(delim->str);
	hd->type = RD_IN;
	delim->str = file;
	delim->is_quotet = 0;
	delim->expand = 0;
}
