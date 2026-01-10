#include "minishell.h"

int	update_oldpwd(t_env_v *env_v)
{
	t_env_v	*oldpwd;
	t_env_v	*current_pwd;

	oldpwd = get_node_envp(env_v, "OLDPWD");
	current_pwd = get_node_envp(env_v, "PWD");
	if (current_pwd)
	{
		if (oldpwd)
		{
			free(oldpwd->value);
			oldpwd->value = ft_str_dup(current_pwd->value);
			if (!oldpwd)
				return (1);
		}
	}
	return (0);
}

int	update_pwd(t_env_v *env_v)
{
	char	*pwd[PATH_MAX];
	t_env_v	*pwd_node;

	if (getcdw(pwd, sizeof(pwd)) == NULL)
	{
		perror("PWD error");
		return (1);
	}
	pwd_node = get_node_envp(env_v, "PWD");
	if (pwd_node)
	{
		free(pwd_node->value);
		pwd_node->value = ft_strdup(pwd);
		if (!pwd_node)
			return (2);
	}
	return (0);
}

void	change_dir(t_shell *shell, char *target)
{
	if (chdir(target) != 0)
	{
		ft_putstr_fd("minishell: cd:", 2);
		ft_putstr_fd(target, 2);
		ft_putendl_fd(": No such file or directory", 2);
		exit_code(1);
	}
	else
	{
		if (update_oldpwd(shell->envp))
			malloc_failure(shell, "change_dir");
		if (update_pwd(shell->envp) == 1)
		{
			exit_code(1);
			return ;
		}
		if (update_pwd(shell->envp) == 2)
			malloc_failure(shell, "change_dir");
		exit_code(0);
	}
}

char	*get_target(t_env_v *env_v, char *input)
{
	t_env_v *old_pwd;

	if (ft_strncmp(input, "-", ft_strlen(input)) == 0)
	{
		old_pwd = get_node_envp(env_v, "OLDPWD");
		if (old_pwd)
			return (old_pwd->value);
	}
	return (input);
}

void	ft_cd(t_shell *shell, t_exec *exec_node)
{
	char	*target;
	t_env_v	*home;

	home = get_node_envp(shell->envp, "HOME");
	if (exec_node->argv[1] && exec_node->argv[2])
		ft_putendl_fd("minishell: cd: too many arguments", 2);
	else
	{
		if (!exec_node->argv[1])
		{
			if (!home || !home->value)
			{
				ft_putendl_fd("Varieble home not set", 2);
				exit_code (1);
				return ;
			}
			else
				target = home->value;
		}
		else
			target = get_target(shell->envp, exec_node->argv[1]);
		if (exec_node->argv[1] && ft_strncmp(exec_node->argv[1], '-', 2) == 0)
			ft_printf("%s\n", target);
		change_dir (shell, target);
	}
}
