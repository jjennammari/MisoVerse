/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miso_structs.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jemustaj <jemustaj@student.42Porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/29 22:48:07 by jemustaj          #+#    #+#             */
/*   Updated: 2026/03/14 17:00:14 by lde-san-         ###   ########.fr       */
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
	bool			expand;
	bool			quotes;
	bool			valid_delim;
	char			*str;
	struct s_token	*next;
	t_token_type	type;
}	t_token;

typedef struct s_line
{
	bool	dquote;
	bool	squote;
	bool	cmd_found;
	int		hd_count;
	t_token	*head;
	t_token	*last_node;
}	t_line;

typedef struct s_shell
{
	int		hd_files;
	int		exit_code;
	char	**envp;
	char	**exp;
	char	*prompt;
	t_token	*node;
	t_line	list;
}	t_shell;

#endif
