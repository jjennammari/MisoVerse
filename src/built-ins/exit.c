
#include <minishell.h>

static int	check_limits(char *str, long long number)
{
	if (number > LLONG_MAX || number < LLONG_MIN)
		return (0);
	if (number == LLONG_MAX && ft_strcmp(str, "9223372036854775807"))
		return (0);
	if (number == LLONG_MIN && ft_strcmp(str, "-9223372036854775808"))
		return (0);
	return (1);
}

static int	is_numeric(char *str)
{
	int			i;
	long long	number;

	i = 0;
	if (!str)
		return (0);
	number = ft_atoll(str);
	if (!check_limits(str, number))
		return (0);
	while (str[i] == ' ')
		i++;
	if (str[i] && (str[i] == '+' || str[i] == '-'))
		i++;
	while (str[i])
	{
		if (str[i] < 48 || str[i] > 57)
			return (0);
		i++;
	}
	return (1);
}

static void is_not_numeric(t_shell *shell, char *str, t_fork *fork)
{
	ft_putstr_fd("minishell: exit: ", 2);
	ft_putstr_fd(str, 2);
	ft_putendl_fd(": numeric argument required", 2);
	cleanup_fork(fork); //THIS FUNCTION SHOULD BE MADE BY JENNA TO CLEAN ALL THE PROCESS on the free_frame.c (fro exemple)
	free_shell_final(shell); //tenho de fazer esta função para fechar o shell - free toda a mem dinamica do shell antes de sair
	exit_code(2); //invalid argument error
	exit(2); //shuts down the process and returns 2 - we can see this '2' when we use echo $? after the process
}

static void	exit_success(t_shell *shell, t_exec	*exec_node, t_fork	*fork)
{
	long long	exit_cd;

	exit_cd = ft_atoll(exec_node->argv[1]);
	if (exec_node->argv[2])
	{
		ft_putstr_fd("minishell: exit: too many arguments\n", 2);
		cleanup_fork(fork);
		free_shell_final(shell);
		exit_code(1);
		exit(1);
	}
	printf_exit(); //tenho de fazer esta função -> em utils.c
	cleanup_fork(fork);
	free_shell_final(shell);
	exit((unsigned char)exit_cd);
}

void	ft_exit(t_shell *shell, t_exec *exec_node, t_fork *fork)
{
	if (!exec_node->argv[1])
		return ;
	if (is_numeric(exec_node->argv[1]))
		exit_success(shell, exec_node, fork);
	else
		is_not_numeric(shell, exec_node, fork);
}
