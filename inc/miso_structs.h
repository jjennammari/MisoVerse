/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miso_structs.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-san- <lde-san-@student.42porto.co      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/29 20:57:19 by lde-san-          #+#    #+#             */
/*   Updated: 2026/02/04 00:44:17 by lde-san-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MISO_STRUCTS_H
# define MISO_STRUCTS_H

# include <stdbool.h>

typedef enum s_token_type
{
	SYS_CMD,
	BLT_CMD,
	PIPE,
	RD_IN,
	RD_OUT,
	APPEND,
	HEREDOC,
	ARG,
}	t_token_type;

typedef struct s_token
{
	t_token_type	type;
	bool			expand;
	char			*str;
	struct s_token	*next;
}	t_token;

typedef struct s_line
{
	t_token	*head;
	t_token	*current;
	t_token	*last_node;
}	t_line;

typedef struct s_shell
{
	int		exit_code;
	char	**envp;
	t_line	list;
	t_token	*node;
}	t_shell;

#endif
