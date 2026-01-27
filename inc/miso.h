/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miso.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-san- <lde-san-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/21 18:29:55 by lde-san-          #+#    #+#             */
/*   Updated: 2026/01/27 21:44:59 by lde-san-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MISO_H
# define MISO_H

// Includes:
# include "./miso_structs.h"
# include "./libft/includes/libft.h"
# include "./miso_structs.h"
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <stdbool.h>
# include <unistd.h>
# include <stdlib.h>
# include <limits.h>
# include <signal.h>
# include <stdio.h>
# include <fcntl.h>
# include <errno.h>

// Text Color:
# define RSET	"\033[0m"
# define B_WI	"\033[1;37m"
# define LIME	"\033[38;2;0;255;0m"
# define BABY	"\033[38;2;0;255;247m"
# define BLOD	"\033[1;38;2;255;0;0m"
# define ORNG	"\033[38;2;255;153;51m"
# define PURP	"\033[1;38;2;174;5;252m"
# define MINT	"\033[1;38;2;55;250;133m"
# define NEOR	"\033[3m\033[38;2;255;153;51m"

         /* Self defined PROMPT */
/* cc with -DPROMPT='"whatever you want :3"' */
# ifndef PROMPT
#  define PROMPT "MisoVerse #"
# endif

// Global Variable:
extern int g_signal;

// Type Re-Definitions:
typedef struct stat t_stat;
typedef struct sigaction t_sigact;

//			Function Prototypes:
//	 -- -- #	miso_launch.c		# -- --
int	miso_launch(t_shell *miso, t_token *head);
//	 -- -- #	main_jenna.c		# -- --
int		main(void);
void	init_variables(t_miso *mv);//NOTE: exit_code init to 0 (= success) is correct?

//	 -- -- #	 fastshell.c		# -- --
void	misoverse_loop(t_miso *mv);//FIX: malloc error handlin

//	 -- -- #	tokenization.c		# -- --
void	create_token_list(t_miso *mv, char *line);//FIX: malloc error handling
void    add_operator(t_line *list, char *line, int *pi);
void	add_redirection(t_line *list, char *line, int *pi);
void	add_argument(t_line *list, char *line, int *pi, *f(char *));

//	 -- -- #  tokenization_utils.c	# -- --
int     is_whitespace(char c);

//	 -- -- #		free.c			# -- --
void	free_misoverse(t_miso *mv);
void	free_token_list(t_miso *mv);

#endif
