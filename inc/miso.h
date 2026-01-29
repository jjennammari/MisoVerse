/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miso.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-san- <lde-san-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/21 18:29:55 by lde-san-          #+#    #+#             */
/*   Updated: 2026/01/29 22:30:51 by lde-san-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MISO_H
# define MISO_H

// Includes:
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
/* Compile with -DPROMPT="Whatever you'd like" */
# ifndef PROMPT
#  define PROMPT "MisoVerse #"
# endif

// Global Variable:
extern int g_signal;

// Type Re-Definitions:
typedef struct stat t_stat;
typedef struct sigaction t_sigact;

//					Function Prototypes:
//	 -- -- #			miso_launch.c			# -- --
int	miso_launch(t_shell *miso, t_token *head);
int miso_call_builtin(t_shell *miso, char **cmd);

//	 -- -- #		  miso_pathfinder.c			# -- --
char	**miso_argv(t_token *head);

//	 -- -- #		 miso_redirection.c			# -- --
void	miso_channeling(int prev_read, t_token *head, int *p, int p_num);

//	 -- -- #	  miso_exec_utils_alpha.c		# -- --
int		miso_is_builtin(char *cmd);
void	miso_free_matrix(char **matrix);
int		miso_waitroom(pid_t child, int *exit_status);
void	miso_call_program(t_shell *miso, char **cmd, char **envp);
void	miso_checknfree(void *check1, char **check2, void *free1, char **free2);

//	 -- -- #	  miso_exec_utils_beta.c		# -- --
int		miso_seg_count(t_token *head);
t_token *miso_next_segment(t_token *head);
void	miso_daddy_pipe_manager(int *prev_read, int *p, int p_num);
int		miso_daddy_exec(t_shell *miso, char **cmd, int *std_cpy, t_token *head);
#endif
