#include "minishell.h"

bool	check_flag(char *str)
{
	int	i;

	i = 1;
	if (str[0] != '-')
		return (false);
	while (str[i] == 'n')
		i++;
	if (str[i] == 0)
		return (true);
	else
		return (false);
}

void	ft_echo(char **args)
{
	int		i;
	bool	print_new_line;

	i 				= 1;
	print_new_line	= true;
	while (args[i] && check_flag(args[i]))
	{
		print_new_line = false;
		i++;
	}
	while (args[i])
	{
		ft_putstr_fd(args[i], 1);
		if (args[i + 1])
			ft_putstr_fd(" ", 1);
		i++;
	}
	if (print_new_line)
		write (1, "\n", 1);
	exit_code (0);
}
