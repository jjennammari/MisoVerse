#include "parsing.h"

int	main(void)
{
	t_miso	mv;

	init_variables(&mv);
	misoverse_loop(&mv);
	return (0);
}

void	init_variables(t_miso *mv)
{
	mv->exit_code = 0;
	mv->node = malloc(sizeof(t_token));
	if (!mv->node)
		return ;
	mv->node->squotes = false;
	mv->node->dquotes = false;
	mv->node->expansion = false;
	mv->node->str = NULL;
	mv->node->next = NULL;
	mv->list.head = NULL;
	mv->list.current = NULL;
	mv->list.last_node = NULL;
}
