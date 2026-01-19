#include "parsing.h"

int	main(void)
{
	t_fshell	*fs;

	init_variables(fs);
	fastshell(fs);
	free(fs);
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
}
