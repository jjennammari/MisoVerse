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
void	init_variables(t_fshell *fs);

/* fastshell.c */
void	fastshell_loop(t_fshell *fs);//FIX: malloc error handling
/* tokenization.c */
void	create_token_list(char *line);//FIX: malloc error handling
/* errors.c *///NOTE: add here functions to print error messages / handle errors ?
void	update_exit_status(t_fshell *fs, int code, int exit_status);
void	print_error_message(t_fshell *fs);
/* exit.c */
void	exit_program(t_fshell *fs);//NOTE: notes inside this function
/* free.c */
void	free_fastshell(t_fshell *fs);
void	free_token_list(t_fshell *fs);

/* Don't have internet so adding questions here:
 * */

#endif
