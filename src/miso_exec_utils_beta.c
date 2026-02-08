/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miso_exec_utils_beta.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-san- <lde-san-@student.42porto.co      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/28 19:45:54 by lde-san-          #+#    #+#             */
/*   Updated: 2026/02/07 16:26:54 by lde-san-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/miso.h"

int		miso_seg_count(t_token *head);
char	**miso_matrixdup(char **matrix);
t_token	*miso_next_segment(t_token *head);
void	miso_daddy_pipe_manager(int *prev_read, int *p, int p_num);

t_token	*miso_next_segment(t_token *head)
{
	while (head)
	{
		if (head->type == PIPE)
		{
			if (!head->next)
				racc_print(2, BLOD"PROMPT"MINT"Error after `%s'\n", head->str);
			head = head->next;
			break ;
		}
		head = head->next;
	}
	return (head);
}
/* Moves the head pointer until the first token after the next pipe "|".
It assumes that it will always be able to find a pipe or the end of the
list. Meaning that it will print an error and return NULL if there is 
nothing after a pipe. On success, it will return either a pointer to the
start of the next segment, or NULL. */

int	miso_seg_count(t_token *head)
{
	int		guide;
	t_token	*trav;

	trav = head;
	guide = 0;
	while (trav)
	{
		if (trav->type == PIPE)
			guide++;
		trav = trav->next;
	}
	if (!guide)
		return (1);
	return (guide + 1);
}
/*Traverses the list looking for pipes, in order to return the number of
segments in the line. By default it returns one as it assumes that the 
input will never be an empty line.*/

void	miso_daddy_pipe_manager(int *prev_read, int *p, int p_num)
{
	if (*prev_read != -1)
		close(*prev_read);
	if (p_num - 1 != 0)
	{
		close(p[1]);
		*prev_read = p[0];
	}
	return ;
}
/* Updates the prev_read variable with the read end of the last pipe
created, and closes the last write end since is no longer needed in
the parent process */

char	**miso_matrixdup(char **matrix)
{
	char	**result;
	int		guide;

	guide = 0;
	while (matrix[guide])
		guide++;
	result = ft_calloc(guide + 1, sizeof(char *));
	if (!result)
	{
		perror(BLOD"PROMPT"RSET);
		return (NULL);
	}
	result[guide] = NULL;
	while (guide-- > 0)
	{
		result[guide] = ft_strdup(matrix[guide]);
		if (!result[guide])
		{
			perror(BLOD"PROMPT"RSET);
			miso_free_matrix(result);
			return (NULL);
		}
	}
	return (result);
}
/* Duplicates the matrix passed as a parameter and returns a copy
to the new matrix or NULL in case of allocation error. */
