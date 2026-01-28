#ifndef PARSING_H
#define PARSING_H

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
#ifndef PROMPT
#define PROMPT "fastshell #"//NOTE: be sure it's okay to use fastshell instead of minishell
#endif

/*  main_jenna.c  */
int		miso_main(void);
void	init_variables(t_shell *miso);//NOTE: exit_code init to 0 (= success) is correct?

/* fastshell.c */
void	misoverse_loop(t_shell *miso);//FIX: malloc error handlin

/* tokenization.c */
void	create_token_list(t_shell *miso, char *line);//FIX: malloc error handling
void    add_operator(t_shell *miso, char *line, int *pi);
void	add_redirection(t_shell *miso, char *line, int *pi);
void	add_argument(t_shell *miso, char *line, int *pi, int (*f)(char));//TODO: keep in mind that expand is true only with specific scenarios
void	add_to_list(t_shell *miso, char *str, t_token_type type);

/* tokenization_utils.c */
int		is_whitespace(char c);
int		is_squote(char c);
int		is_dquote(char c);

/* free.c */
void	free_misoverse(t_shell *miso);
void	free_token_list(t_shell *miso);

/* functions to delete after connecting with libft */
char	*ft_strchr(const char *s, int c);
size_t	ft_strlen(const char *s);
size_t	ft_strlcpy(char *dst, const char *src, size_t size);
char	*ft_strdup(const char *s);

#endif
