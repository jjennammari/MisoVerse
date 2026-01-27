/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-san- <lde-san-@student.42porto.co      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 22:39:01 by lde-san-          #+#    #+#             */
/*   Updated: 2025/06/07 09:05:31 by lde-san-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

# ifndef MAX_FD
#  define MAX_FD 1024
# endif

# include <stdlib.h>
# include <fcntl.h>
# include <unistd.h>
# include <stddef.h>

typedef struct s_lst
{
	char			letter;
	struct s_lst	*tail;
	struct s_lst	*next;
}	t_lst;

char	*get_next_line(int fd);
int		extract_buffer(t_lst **head, int fd);
char	*get_lines(t_lst **head);
t_lst	*racc_lstnew(char c);
size_t	racc_linesize(t_lst *lst);
int		racc_findend(t_lst **lst);
void	racc_delnode(t_lst **lst, int clear_all);
int		racc_lstadd(t_lst **lst, t_lst *new);

#endif
