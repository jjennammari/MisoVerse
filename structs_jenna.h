#ifndef STRUCTS_JENNA
#define STRUCTS_JENNA

typedef enum	s_token_type
{
	CMD,
	RD_IN,
	RD_OUT,
	APPEND,
	HEREDOC,
	PIPE,
	ARG,
} t_token_type;

typedef struct	s_token
{
	t_token_type	type;
	char			*str;
	struct s_token	*next;
	int				index;
} t_token;

typedef struct	s_line
{
	t_token			*node;
	struct s_line	*head;
	struct s_line	*current;

} t_line;

typedef struct	s_fshell
{
	int		exit_code;//NOTE: should I still make this static ?
	t_token	*node;
	t_line	*list;
} t_fshell;

#endif
