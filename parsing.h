#ifndef PARSING_H
#define PARSING_H

# include "structs_jenna.h"
# include <unistd.h>
/* NULL */
# include <stdlib.h>
/* malloc */
# include <readline/readline.h>
/* readline, cc with -lreadline */
# include <readline/history.h>
/* add_history */

         /* Self defined PROMPT */
/* cc with -DPROMPT='"whatever you want :3"' */
#ifndef PROMPT
#define PROMPT "fastshell #"//NOTE: be sure it's okay to use fastshell instead of minishell
#endif

/*  main_jenna.c  */
int		main(void);
void	init_variables(t_miso *mv);//NOTE: exit_code init to 0 (= success) is correct?

/* fastshell.c */
void	misoverse_loop(t_miso *mv);//FIX: malloc error handlin

/* tokenization.c */
int	create_token_list(t_miso *mv, char *line);//FIX: malloc error handling
void    add_operator(t_line *list);
void    add_bltin(t_line *list);
void    add_arg(t_line *list);
void    add_new_node(t_line *list);

/* tokenization_utils.c */
int     is_whitespace(char c);
int     is_operator(char c);
int     is_bltin(char c);
void    add_redirections(t_line *list);

/* errors.c *///NOTE: add here functions to print error messages / handle errors?
void	update_exit_status(t_miso *mv, int code, int exit_status);
void	print_error_message(t_miso *mv);

/* exit.c */
void	exit_program(t_miso *mv);//NOTE: notes inside this function

/* free.c */
void	free_misoverse(t_miso *mv);
void	free_token_list(t_miso *mv);

/* functions to delete after connecting with libft */
char	*ft_strchr(const char *s, int c);

#endif
