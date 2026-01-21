#include "parsing.h"

int	main(void)
{
	t_miso	*mv;

	init_variables(mv);
	misoverse_loop(mv);
	return (0);
}

void	init_variables(t_miso *mv)
{
	mv->exit_code = 0;
	mv->node = NULL;
	mv->list = NULL;
	mv->node->str = NULL;
	mv->node->next = NULL;
	mv->list->head = NULL;
	mv->list->current = NULL;
	mv->list->last_node = NULL;
}
