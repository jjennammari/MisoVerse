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
void	init_variables(t_line **list);//FIX: malloc error handling

/* fastshell.c */
void	fastshell_jenna(t_line **list);//FIX: malloc error handling
/* tokenization.c */
void	create_tokens(t_line **list, char *line);

#endif
