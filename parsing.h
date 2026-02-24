/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jemustaj <jemustaj@student.42Porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/12 16:31:45 by jemustaj          #+#    #+#             */
/*   Updated: 2026/02/24 15:11:44 by jemustaj         ###   ########.fr       */
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
#  define PROMPT "misoverse #"
# endif

/*  main_jenna.c  */
int		main(void);
void	init_variables(t_shell *miso);//NOTE: exit_code init to 0 (= success) is correct?

/* fastshell.c */
void	misoverse_loop(t_shell *miso);//TODO: check continue actually skips all and starts the loop from beginning

/* tokenization.c */
void	miso_tokenization(t_shell *miso, char *line);
void	add_operator(t_shell *miso, char *line, int *pi);
void	add_redirection(t_shell *miso, char *line, int *pi);
void	add_argument(t_shell *miso, char *line, int *pi, int (*f)(char));
void	add_to_list(t_shell *miso, char *str, t_token_type type);

/* miso_tokenization_quotes */
void	add_quotes(t_shell *miso, char *str, int *pi, int (*f)(char));
int		validate_quotes(t_shell *miso, const char *str, int (*f)(char));
int		is_squote(char c);
int		is_dquote(char c);

/* tokenization_utils.c */
int		is_whitespace(char c);
char	*create_token_str(char *str, int len);

/* miso_parser.c */
int		miso_parsing(t_shell *miso);

/* miso_parser_utils.c */
int		is_builtin(char *word);
void	set_commandtype(t_shell *miso, t_token *node);

/* miso_expand_variable.c */
void	miso_expand_variable(char *str);//TODO: need to increase i variable after else condition handling
char	*get_var_name(char *str, int *pi);//TODO: check that len = i++ is correct way to add i + 1 to len
char	*add_to_string(char *s1, char *s2);
int		ft_isalnum(char c);

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
