#include "parsing.h"

void	free_misoverse(t_miso *mv)
{
	if (mv->list.head != NULL)
		free_token_list(mv);
}

void	free_token_list(t_miso *mv)
{
//	while (mv->list->head != NULL)
}
