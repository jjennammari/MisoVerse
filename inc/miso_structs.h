/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miso_structs.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jemustaj <jemustaj@student.42Porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/29 22:48:07 by jemustaj          #+#    #+#             */
/*   Updated: 2026/02/24 21:14:23 by lde-san-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MISO_STRUCTS_H
# define MISO_STRUCTS_H

# include <stdbool.h>

typedef enum s_token_type
{
	SYS_CMD,
	BLT_CMD,
	RD_IN,
	RD_OUT,
	APPEND,
	HEREDOC,
	ARG,
	PIPE,
}	t_token_type;

typedef struct s_token
{
	t_token_type	type;
	int				expand;
	char			*str;
	struct s_token	*next;
}	t_token;

typedef struct s_line
{
	int		cmd_found;
	int		syntax_err;
	t_token	*head;
	t_token	*last_node;
}	t_line;

typedef struct s_shell
{
	int		exit_code;
	char    **envp;
	char    **exp;
	t_token	*node;
	t_line	list;
}	t_shell;

#endif
