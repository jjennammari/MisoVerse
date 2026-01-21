#include <minishell.h>

void	ft_pwd(void)
{
	char	directory[PATH_MAX];

	if (getcwd(directory, sizeof(directory)) != NULL)
		ft_putendl_fd(directory, 1);
	else
	{
		perror("pwd error");
		exit_code(1);
	}
}