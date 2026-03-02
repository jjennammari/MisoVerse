/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miso_exec_utils_alpha.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-san- <lde-san-@student.42porto.co      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/28 19:41:47 by lde-san-          #+#    #+#             */
/*   Updated: 2026/03/02 09:39:53 by lde-san-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/miso.h"

int		miso_waitroom(pid_t child, int *exit_status);
void	miso_call_program(t_shell *miso, char **cmd, t_token *head);
int		(*miso_get_builtin(char *cmd))(t_shell *miso, char **cmd);
int		miso_rn(t_shell *m, char **c, t_token *h, int (*f)(t_shell *, char **));

void	miso_call_program(t_shell *miso, char **cmd, t_token *head)
{
	int	exit_code;
	int	(*built_in)(t_shell *, char **);

	exit_code = 127;
	built_in = miso_get_builtin(cmd[0]);
	if (built_in)
		exit_code = miso_rn(miso, cmd, head, built_in);
	else
	{
		miso_exp_filter(miso->exp, miso->envp);
		execve(cmd[0], cmd, miso->envp);
	}
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

int	(*miso_get_builtin(char *cmd))(t_shell *miso, char **cmd)
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
