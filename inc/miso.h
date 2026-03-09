/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miso.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-san- <lde-san-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/21 18:29:55 by lde-san-          #+#    #+#             */
/*   Updated: 2026/03/09 19:13:15 by lde-san-         ###   ########.fr       */
/*   Updated: 2026/03/08 18:46:26 by lde-san-         ###   ########.fr       */
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
# include <stdlib.h>
# include <fcntl.h>
# include <errno.h>

// Miso Colors:
# define RSET	"\033[0m"
# define B_WI	"\033[1;37m"
# define LIME	"\033[38;2;0;255;0m"
# define BABY	"\033[38;2;0;255;247m"
# define BLOD	"\033[1;38;2;255;0;0m"
# define ORNG	"\033[38;2;255;153;51m"
# define PURP	"\033[1;38;2;174;5;252m"
# define MINT	"\033[1;38;2;55;250;133m"
# define NEOR	"\033[3m\033[38;2;255;153;51m"

//			Self defined PROMPT
// Compile with -DPROMPT="Whatever you'd like"
# ifndef PROMPT
#  define PROMPT "\033[1;38;2;55;250;133m misoverse \033[1;38;2;174;5;252m» \033[0m"
# endif

// Global Variable:
extern int					g_signal;

// Type Re-Definitions:
typedef struct stat			t_stat;
typedef struct sigaction	t_sigact;

//			Function Prototypes:

/*  miso_main.c  */
int		main(int argc, char **argv, char **envp); //NOTE: exit_code init to 0 (= success) is correct?

/* misoverse_loop.c */
void	misoverse_loop(t_shell *miso);//TODO: check continue actually skips all and starts the loop from beginning

/* tokenization.c */
int		miso_tokenize(t_shell *miso, char *line);
void	miso_add_operator(t_shell *miso, char *line, int *pi);
void	miso_add_redirection(t_shell *miso, char *line, int *pi);
void	miso_add_argument(t_shell *miso, char *line);//TODO: delete recieved function parameter
void	miso_add_to_list(t_shell *miso, char *str, t_token_type type);

/* miso_tokenization_quotes */
int		miso_add_quotes(t_shell *miso, char *str, int *pi, int (*f)(char));
int		miso_validate_quotes(t_shell *miso, const char *str, int (*f)(char));
int		miso_is_squote(char c);
int		miso_is_dquote(char c);

/* tokenization_utils.c */
int		miso_is_whitespace(char c);
char	*miso_create_token_str(char *str, int len);

/* miso_parser.c */
int		miso_parse(t_shell *miso);
int		miso_parse_redirections(t_shell *miso, t_token *node);
int		miso_parse_pipe(t_shell *miso, t_token *node);

/* miso_parser_utils.c */
int		miso_is_builtin(char *word);
void	miso_set_commandtype(t_shell *miso, t_token *node);
void	miso_search_cmd(t_shell *miso, t_token *node);
int		miso_is_redirection(t_token_type type);

/* miso_heredoc.c */
int		miso_heredoc(t_shell *miso);
int		miso_get_heredoc(t_shell *miso, t_token *hd, int file_nb);
void	miso_hd_update_nodes(t_token *hd, t_token *delim, char *file);
int		miso_hd_open_file(char *file, int *fd);
char	*miso_hd_get_filename(int file_nb);
int		miso_hd_collect(t_shell *miso, t_token *delim, int fd);
int		miso_hd_found_delim(char *line, char *delim);
char	*miso_hd_check_expansion(t_shell *miso, t_token *delim, char *line);
int		miso_hd_write(char *line, int fd);

/* miso_expand_.c */
char	*miso_expand(t_shell *miso, char *str);
char	*miso_get_exp_name(t_shell *miso, char *str, int *pi);
char	*miso_subtract_exp_name(char *str, int len);
char	*miso_add_to_str(char *s1, char *s2);
void	miso_expand_node(t_shell *miso, t_token *node, char *str);
char	*miso_expand_line(t_shell *miso, char *line);
int		miso_is_alnum(char c);

/* miso_free.c */
void 	miso_reset(t_shell *miso);
void	miso_free_token_list(t_shell *miso);
void    misoverse_free(t_shell *miso, int print_err);

/* delete_later.c */
void	miso_print_token_list(t_shell *miso);

//	 -- -- #	miso_launch.c
int		miso_launch(t_shell *miso, t_token *head);

//	 -- -- #	miso_pathfinder.c
char	**miso_argv(t_token *head, char **envp);

//	 -- -- #	miso_redirection.c
void	miso_channeling(int prev_read, t_token *head, int *p, int p_num);

//   -- -- #    miso_signals.c
void    miso_fdshutdown(void);
void    miso_daddy_sigint(int sig);
void    miso_init_daddy_signals(void);
void    miso_setup_child_signals(void);

//	 -- -- #	miso_exec_utils_alpha.c
int		miso_waitroom(pid_t child, int *exit_status);
void	miso_call_program(t_shell *miso, char **cmd, t_token *head);
int     (*miso_get_builtin(char *cmd))(t_shell *miso, char **cmd);
int     miso_rn(t_shell *m, char **c, t_token *h, int (*f)(t_shell *, char **));

//	 -- -- #	miso_exec_utils_beta.c
int		miso_seg_count(t_token *head);
char    **miso_matrixdup(char **matrix);
t_token	*miso_next_segment(t_token *head);
void	miso_daddy_pipe_manager(int *prev_read, int *p, int p_num);

//   -- -- #    miso_exec_utils_charlie.c
void	miso_free_matrix(char **matrix);
int		miso_freenret(void *free1, void *free2, int p_err, int ret);
void    miso_checknfree(void *check1, char **check2, void *free1, char **free2);

//   -- -- #    miso_environment_utils_alpha.c
char	**miso_envinit(char **envp);
char    *miso_getenv(const char *key, char **envp);
int		miso_add_envar(char ***envp, char *key, char *varlue);
int		miso_envar_update(char **envp, char *key, char *new_value);
char	*miso_find_envar(char **envp, const char *key, int *guide);

//   -- -- #    miso_environment_utils_beta.c
char    *miso_get_key(char *var);
int     miso_envarcmp(const char *var, const char *key);
char    *miso_remove_envar(char **envp, const char *key);
char	*miso_extract_variable(char **envp, const char *key);
int     miso_env_addorupdate(char ***envp, char *key, char *varlue);

//   -- -- #    miso_environment_utils_charlie.c
void	miso_keyvariables_init(char ***envp);

//   -- -- #    miso_export_utils_alpha.c
int		miso_addexp(t_shell *miso, char *key);
int		miso_isvarinexp(char **exp, char *var);
void	miso_removexp(t_shell *miso, char *key);
void	miso_exp_innit(t_shell *miso, char *path_valid);
char	*miso_expcheck(char **exp, char *key, int *index);

//   -- -- #    miso_export_utils_beta.c
void	miso_exp_filter(char **exp, char **envp);
int		miso_export_sort(t_shell *miso, char **envp, int envp_c);
int     miso_exp_addorupdate(t_shell *m, char ***env, char *key, char *var);

//    -- -- #	Built in Functions: miso_(builtin).c
int		miso_cd(t_shell *miso, char **argv);
int		miso_pwd(t_shell *miso, char **argv);
int		miso_env(t_shell *miso, char **argv);
int		miso_echo(t_shell *miso, char **argv);
int		miso_exit(t_shell *miso, char **argv);
int		miso_unset(t_shell *miso, char **argv);
int		miso_export(t_shell *miso, char **argv);
#endif
