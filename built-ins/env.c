#include <minishell.h>

static int	aux_remove(t_shell *shell, int *i, int *size)
{
	int		j;
	char	**new_envp;

	free(shell->envp[*i]);
	j = *i;
	while (shell->envp[j + 1])
	{
		shell->envp[j] = shell->envp[j + 1];
		j++;
	}
	new_envp = (char **)realloc(shell->envp, sizeof(char *) * (*size));
	if (!new_envp)
		return (1);
	shell->envp = new_envp;
	shell->envp[*size - 1] = NULL;
	return (0);
}

int	remove_var_envp(t_shell *shell, char *key)
{
	int	i;
	int	len;
	int	size;

	i = 0;
	len = ft_strlen(key);
	size = 0;
	while (shell->envp[size])
		size++;
	while (shell->envp[i])
	{
		if (!ft_strncmp(shell->envp[i], key, len) && shell->envp[i][len] == '=')
		{
			aux_remove(shell, &i, &size);
			break;
		}
		i++;
	}
	return (0);
}

int	add_var_envp(t_shell *shell, char *key, char *value)
{
	int		i;
	char	*str;
	char	**new_envp;

	i = 0;
	str = ft_strjoin(key, value);
	if (!str)
		malloc_failure(shell, "add_var_envp");
	while (str[i])
		i++;
	new_envp = (char **)realloc(shell->envp, sizeof(char *) * (i + 2));
	if (!new_envp)
		return (1);
	shell->envp = new_envp;
	shell->envp[i] = str;
	shell->envp[i + 1] = NULL;
	return (0);
}

char	**duplicate_envp(char **envp)
{
	int		i;
	char	**new_envp;

	i = 0;
	while (envp[i])
		i++;
	new_envp = (char **)malloc((i + 1) * sizeof(char *));
	if (!new_envp)
		return (NULL);
	i = 0;
	while (envp[i])
	{
		new_envp[i] = ft_strdup(envp[i]);
		if (!new_envp)
		{
			while (--i >= 0)
				free(new_envp[i]);
			return (free(new_envp), NULL);
		}
		i++;
	}
	new_envp[i] = NULL;
	return (new_envp);
}

void	ft_env(char	**envp, char	**arguments)
{
	int	i;

	if (arguments[1])
	{
		print_error("env", NULL, arguments[1], "No such file or directory");
		exit_code(1);
		return ;
	}
	i = 0;
	while (envp[i])
	{
		ft_printf("%s\n", envp[i]);
		i++;
	}
}