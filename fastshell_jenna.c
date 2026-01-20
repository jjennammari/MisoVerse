#include "parsing.h"

void	fastshell_loop(t_fshell *fs)
{
	char	*line;

	while (1)
	{
		//somewhere here handle received signals? read more about signals!
		line = readline(PROMPT);
		if (!line)
			update_exit_status(fs, 2, 1);
		//instead return: create exit function to handle error and exit ?
		add_history(line);
		create_token_list(line);
		//parse_token_list(fs); + variable expansion
		//send fs to execution
	}
}
