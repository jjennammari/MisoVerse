#include "parsing.h"

void	misoverse_loop(t_miso *mv)
{
	char	*line;

	while (1)
	{
		//somewhere here handle received signals? read more about signals!
		line = readline(PROMPT);
		if (!line)
			exit_program(mv);
		add_history(line);
		if (create_token_list(mv, line) == 0)
			continue;
		//parse_token_list(fs); + variable expansion
		//send fs to execution
	}
}
