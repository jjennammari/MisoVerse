/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jemustaj <jemustaj@student.42Porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/12 16:31:45 by jemustaj          #+#    #+#             */
/*   Updated: 2026/02/13 13:47:07 by jemustaj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include <unistd.h>
/* NULL */
# include <stdlib.h>
/* malloc */
# include <readline/readline.h>
/* readline, cc with -lreadline */
# include <readline/history.h>
/* add_history */
# include <stdbool.h>
# include "miso_structs.h"

		/* Self defined PROMPT */
/* cc with -DPROMPT='"whatever you want :3"' */
# ifndef PROMPT
#  define PROMPT "fastshell #"//NOTE: be sure it's okay to use fastshell instead of minishell
# endif

/*  main_jenna.c  */
int		main(void);
void	init_variables(t_shell *miso);//NOTE: exit_code init to 0 (= success) is correct?

/* fastshell.c */
void	misoverse_loop(t_shell *miso);//FIX: malloc error handlin

/* tokenization.c */
void	miso_token_list(t_shell *miso, char *line);//FIX: malloc error handling
void	add_operator(t_shell *miso, char *line, int *pi);
void	add_redirection(t_shell *miso, char *line, int *pi);
void	add_argument(t_shell *miso, char *line, int *pi, int (*f)(char));//TODO: keep in mind that expand is true only with specific scenarios FIX: malloc error handling
void	add_to_list(t_shell *miso, char *str, t_token_type type);//FIX: malloc error handling

/* tokenization_utils.c */
int		is_whitespace(char c);
int		is_squote(char c);
int		is_dquote(char c);
int		is_builtin(char *word);
void	set_commandtype(t_shell *miso);

/* miso_parser.c */

/* free.c */
void	misoverse_free(t_shell *miso);
void	free_token_list(t_shell *miso);

/* ft_strlen.c */
size_t	ft_strlen(const char *s);

/* ft_strchr.c*/
char	*ft_strchr(const char *s, int c);

/* delete_later.c */
void	print_token_list(t_shell *miso);

#endif
