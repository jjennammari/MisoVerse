/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miso_structs.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jemustaj <jemustaj@student.42Porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/29 22:48:07 by jemustaj          #+#    #+#             */
/*   Updated: 2026/02/13 13:01:26 by jemustaj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MISO_STRUCTS_H
# define MISO_STRUCTS_H

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
	int				expand;
	t_token_type	type;
	char			*str;
	struct s_token	*next;
}	t_token;

typedef struct s_line
{
	int		cmd_found;
	t_token	*head;
	t_token	*last_node;
}	t_line;

typedef struct s_shell
{
	int		exit_code;
	t_token	*node;
	t_line	list;
}	t_shell;

#endif
