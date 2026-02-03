/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miso_exec_utils_beta.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-san- <lde-san-@student.42porto.co      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/28 19:45:54 by lde-san-          #+#    #+#             */
/*   Updated: 2026/02/02 19:05:36 by lde-san-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/miso.h"

int		miso_seg_count(t_token *head);
t_token	*miso_next_segment(t_token *head);
void	miso_daddy_pipe_manager(int *prev_read, int *p, int p_num);
int		miso_daddy_exec(t_shell *miso, char **cmd, int *std_cpy, t_token *head);
int		miso_rn(t_shell *m, char **c, t_token *h, int (*f)(t_shell *, char **));

int	miso_rn(t_shell *m, char **c, t_token *h, int (*f)(t_shell *, char **))
{
	int	exit_code;
	int	std_cpy[2];

	exit_code = 127;
	std_cpy[0] = dup(0);
	std_cpy[1] = dup(1);
	if (std_cpy[0] == -1 || std_cpy[1] == -1)
	{
		perror(BLOD"PROMPT"RSET);
		return (1);
	}
	miso_channeling(0, h, NULL, -1);
	if (f)
		exit_code = f(m, c);
	dup2(std_cpy[0], 0);
	dup2(std_cpy[1], 1);
	close(std_cpy[0]);
	close(std_cpy[1]);
	miso_free_matrix(c);
	return (exit_code);
}
/* Creates a copy of the stdin and stdout, in order to be able to reestablish
them after execution when there're redirections in the command. The function
is meant to be used in the parent process, so it will return  an exit code 
instead of using exit(). It executes the built-in function passed, and it will
return its exit code, 1 on dup error, or 127 if the pointer to function comes
NULL. */

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
