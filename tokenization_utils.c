#include "parsing.h"

int	is_whitespace(char c)
{
	if (c == 32 || c >= 9 && c <= 13)
		return (1);
	return (0);
}

int	is_squote(char c)
{
	if (c == '\'')
		return (1);
	return (0);
}

int	is_dquote(char c)
{
	if (c == '"')
		return (1);
	return (0);
}

void	create_new_node(t_shell *miso, char *str, t_token_type type)
{
	t_token	*new_node;

	new_node = malloc(sizeof(t_token));
	if (!new_node)
		// free linked list
		return ;
}
