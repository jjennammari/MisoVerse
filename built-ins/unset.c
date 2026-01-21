/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miguelhenriques <miguelhenriques@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 12:22:19 by cda-fons          #+#    #+#             */
/*   Updated: 2025/11/06 16:00:06 by miguelhenri      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static t_env_v	*remove_head(t_env_v *head);

static t_env_v *remove_env_var(t_env_v *head, char *key)
{
	t_env_v	*prev;
	t_env_v	*current;

	if (!head || !key)
		return (NULL);
	if (ft_strcmp(head->key, key) == 0)
		return (head = remove_head(head));
	prev = head;
	current = head->next;
	while (current)
	{
		if (ft_strcmp(current->key, key) == 0)
		{
			prev->next = current->next;
			free(current->key);
			if (current->value)
				free(current->value);
			free(current);
			return (head);
		}
		prev = current;
		current = current->next;
	}
	return (head);
}

static	t_env_v	*remove_head(t_env_v *head)
{
	t_env_v	*temp;

	temp = head;
	head = head->next;
	free(temp->key);
	free(temp->value);
	free(temp);
	return (head);
}

void	ft_unset(t_shell *shell, char **argv)
{
	int		i;
	t_env_v	*aux;

	i = 0;
	while (argv[i])
	{
		aux = get_node_envp(shell->env_v, argv[i]); //ask Jenna to create this function inside srcs/utils/utils_linked_list.c
		if (aux && aux->value)
			remove_var_envp(shell, argv[i]);
		if (aux)
			shell->env_v = remove_env_var(shell,aux->key);
		i++;
	}
}