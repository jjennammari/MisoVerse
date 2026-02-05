/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miguelhenriques <miguelhenriques@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/19 16:01:48 by mreinald          #+#    #+#             */
/*   Updated: 2025/11/06 16:03:17 by miguelhenri      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static void	parse_of_argv(t_shell *shell, char *argv)
{
	if (check_identifier(argv)) //criar em utils.c
	{
		if(!(strchr(argv, '=')))
		{
			if (check_duplicate(shell, shell->env_v, argv)) //criar export_utils2.c
			;
			else
				shell->env_v = set_only_key(shell->env_v, argv); //criar em export_utils.c
		}
		else
		{
			if (check_duplicate(shell, shell->env_v, argv))
			{
				if (update_value(shell, shell->env_v, argv))
					malloc_failure(shell, "parse_of_argv)");
			}
			else
				shell->env_v = key_and_value(shell, shell->env_v, argv);
		}
	}
}

static t_env_v	*aux_key_value(t_env_v *env_v, t_env_v *new_node, int position)
{
	int	i;
	t_env_v	*head;
	t_env_v *save;

	i = 1;
	head = env_v;
	while (i++ < position && env_v)
		env_v = env_v->next;
	save = env_v->next;
	env_v->next = new_node;
	new_node->next = save;
	return (head);
}

t_env_v	*key_and_value(t_shell *shell, t_env_v *env_v, char *argv)
{
	char	**matrix;
	char	*value;
	t_env_v	*new_node;
	int		position;

	matrix = ft_split(argv, '=');
	if (!matrix || !matrix[0])
	{
		if (matrix)
			clean_matrix(matrix); //ask Jenna to make this function on free/utils_free.c
		return (env_v);
	}
	value = ft_strchr(argv, '=');
	new_node = create_node(matrix[0], value + 1); //ask Jenna to make this function on free/utils_free.c
	if (!new_node)
		return (clean_matrix(matrix), env_v); //ask Jenna to make this function on free/utils_free.c
	position = find_position(env_v, new_node->key, linked_env_size(env_v));
	if (position == 0)
		return (new_node->next = env_v, new_node);
	env_v = aux_key_value(env_v, new_node, position);
	add_var_envp(shell, matrix[0], value);
	clean_matrix(matrix);
	return (env_v);
}

static void	print_all_var(t_env_v *env_v)
{
	while (env_v)
	{
		if (env_v->value)
			ft_printf("declare -x %s=\"%s\"\n", env_v->key, env_v->value);
		else
			ft_pritnf("declare -x %s\n", env_v->key);
		env_v = env_v->next;
	}
}

void	ft_export(t_shell *shell, char **argv)
{
	int	i;

	i = 0;
	ft_sort_linked(shell->env_v); //criar esta função em srcs/utils/export_utils.c
	if (!argv[1])
		print_all_var(shell->env_v);
	else
	{
		if (check_append(argv[1])) //criar esta função em srcs/utils/export_utils.c
			set_with_append(shell, shell->env_v, argv[1]); //criar esta função em srcs/utils/export_utils.c
		else
		{
			argv += 1;
			while (argv[i])
			{
				parse_of_argv(shell, argv[i]);
				i++;
			}
		}
	}
}
