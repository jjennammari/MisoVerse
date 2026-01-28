#include "parsing.h"

void	misoverse_loop(t_shell *miso)
{
	char	*line;

	while (1)
	{
		//somewhere here handle received signals? read more about signals!
		line = readline(PROMPT);
		if (!line)
			return ;
		add_history(line);
		create_token_list(miso, line);
		//parse_token_list(fs); + variable expansion
		//send fs to execution
	}
}
