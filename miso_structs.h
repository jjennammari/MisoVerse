#ifndef MISO_STRUCTS
#define MISO_STRUCTS


typedef enum	s_token_type
{
	SYS_CMD,
	BLT_CMD,
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
	bool			expand;
	char			*str;
	struct s_token	*next;
} t_token;

typedef struct	s_line
{
	t_token	*head;
	t_token	*current;//TODO: delete if not needed
	t_token	*last_node;//TODO: delete if not needed, also delete from add_new_token
} t_line;

typedef struct	s_shell
{
	int		exit_code;
	t_line	list;
	t_token	*node;
} t_shell;

#endif
