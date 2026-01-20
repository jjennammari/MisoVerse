#include "parsing.h"

int	main(void)
{
	t_fshell	*fs;

	init_variables(fs);
	fastshell_loop(fs);
	return (0);
}

void	init_variables(t_fshell *fs)
{
	fs->node = NULL;
	fs->list = NULL;
	fs->list->node->str = NULL;
	fs->list->node->next = NULL;
	fs->list->node->index = 0;
	fs->list->head = NULL;
	fs->list->current = NULL;
	fs->list->temp = NULL;
}
