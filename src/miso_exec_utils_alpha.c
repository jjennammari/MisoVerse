/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miso_exec_utils_alpha.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-san- <lde-san-@student.42porto.co      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/28 19:41:47 by lde-san-          #+#    #+#             */
/*   Updated: 2026/02/03 15:02:47 by lde-san-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/miso.h"

void	miso_free_matrix(char **matrix);
int		miso_waitroom(pid_t child, int *exit_status);
void	miso_call_program(t_shell *miso, char **cmd, t_token *head);
int		(*miso_is_builtin(char *cmd))(t_shell *miso, char **cmd);
void	miso_checknfree(void *check1, char **check2, void *free1, char **free2);

void	miso_call_program(t_shell *miso, char **cmd, t_token *head)
{
	int	exit_code;
	int	(*built_in)(t_shell *, char **);

	exit_code = 127;
	built_in = miso_is_builtin(cmd[0]);
	if (built_in)
		exit_code = miso_rn(miso, cmd, head, built_in);
	else
		execve(cmd[0], cmd, miso->envp);
	if (exit_code == 0)
	{
		miso_free_matrix(cmd);
		exit(0);
	}
	perror(BLOD"PROMPT"RSET);
	miso_free_matrix(cmd);
	exit(exit_code);
}
/* Determines whether the comand will be executed with execve or
ran with a built-in function. In either case it is expected for
the "execution" to take over and exit accordingly, therefore, if
the function reaches the perror line, it assumes that an error
ocurred, and the function exits accordingly. */

int	miso_waitroom(pid_t child, int *exit_status)
{
	waitpid(child, exit_status, 0);
	while (wait(NULL) > 0)
		continue ;
	if (WIFEXITED(*exit_status))
		return (WEXITSTATUS(*exit_status));
	else if (WIFSIGNALED(*exit_status))
		return (128 + WTERMSIG(*exit_status));
	return (0);
}
/* Waits for the passed process ID to finish, in order to translate the 
exit status into the exit code that will be returned. While the proyect
doesn't ask to handle other stop reasons like WIFCONTINUED or WIFSTOPPED,
they are a posibility. That posibility, we've decided to handle as a successful
end, so the function will return 0 by default.*/

int	(*miso_is_builtin(char *cmd))(t_shell *miso, char **cmd)
{
	size_t	len;

	len = ft_strlen(cmd);
	if ((len == 4) && !ft_strncmp("echo", cmd, len))
		return (&miso_echo);
	if ((len == 2) && !ft_strncmp("cd", cmd, len))
		return (&miso_cd);
	if ((len == 3) && !ft_strncmp("pwd", cmd, len))
		return (&miso_pwd);
	if ((len == 6) && !ft_strncmp("export", cmd, len))
		return (&miso_export);
	if ((len == 5) && !ft_strncmp("unset", cmd, len))
		return (&miso_unset);
	if ((len == 3) && !ft_strncmp("env", cmd, len))
		return (&miso_env);
	if ((len == 4) && !ft_strncmp("exit", cmd, len))
		return (&miso_exit);
	return (NULL);
}
/* Uses ft_strncmp and the lenght of the incoming string "cmd" to analyze
if the command being called is one of the built-in functions. It will 
return a pointer to said function, or NULL if is not one of the listed 
commands. */

void	miso_checknfree(void *check1, char **check2, void *free1, char **free2)
{
	if (check1 || check2)
		return ;
	perror(BLOD"PROMPT"RSET);
	if (free1)
		free(free1);
	if (free2)
		miso_free_matrix(free2);
	exit(1);
}
/* Mainly for checking memory allocations, this option takes either a * or
** pointer to check and one to free previous dependencies if necessary. The
function will print the message from errno if necessary and exit with 
EXIT_FAILURE */

void	miso_free_matrix(char **matrix)
{
	int	guide;

	if (!matrix)
		return ;
	guide = 0;
	while (matrix[guide])
	{
		free(matrix[guide]);
		guide++;
	}
	free(matrix);
	return ;
}
/*Traverses all the pointers in the 2D array passed, freeing its contents and
eventually the array itself. It assumes that all pointers in the array either
are allocated or NULL, and that the array has a NULL pointer only at the end.*/
