#include "parsing.h"

void	fastshell_jenna(t_line **list)
{
	char	*line;

	while (1)
	{
		line = readline(PROMPT);
		if (!line)
			return ;
		add_history(line);
		create_tokens(list, line);
	}
}
