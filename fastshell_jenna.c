#include "parsing.h"

void	fastshell(t_line *list)
{
	char	*line;

	while (1)
	{
		line = readline(PROMPT);
		if (!line)
			return ;
		add_history(line);
		create_tokens(&list, line);
	}
}
