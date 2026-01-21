#ifndef STRUCTS_JENNA
#define STRUCTS_JENNA

typedef enum	s_token_type
{
	CMD,
	BLTIN,
//	FILE,
	PIPE,
	RD_IN,
	RD_OUT,
	APPEND,
	HEREDOC,
	ARG,
} t_token_type;

typedef struct	s_token
{
	t_token_type	type;
	char			*str;
	struct s_token	*next;
} t_token;

typedef struct	s_line
{
	t_token	*head;
	t_token	*current;
	t_token	*last_node;
} t_line;

typedef struct	s_miso
{
	int		exit_code;//NOTE: should I still make this static because not dynamically allocating memory to it?
	t_token	*node;
	t_line	*list;
} t_miso;

#endif
