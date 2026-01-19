#include "parsing.h"

void	fastshell(t_fshell *fs)
{
	char	*line;

	while (1)
	{
		line = readline(PROMPT);
		if (!line)
			return ;
		//instead return: create exit function to handle error and exit ?
		add_history(line);
		create_tokens(line);
		//send fs and line to parsing, variable expansion
		//send fs and line to execution
	}
}
