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
