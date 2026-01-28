#include "parsing.h"

void	free_misoverse(t_shell *miso)
{
	if (miso->list.head != NULL)
		free_token_list(miso);
}

void	free_token_list(t_shell *miso)
{
//	while (mv->list->head != NULL)
}
