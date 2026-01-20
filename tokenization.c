# include "parsing.h"

void	create_token_list(char *line)
{
	t_line	*list;

	list = malloc(sizeof(t_line));
	if (!list)
		update_exit_status(fs, 2, 1);
}
