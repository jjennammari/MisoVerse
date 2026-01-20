#include "parsing.h"

void	free_fastshell(t_fshell *fs)
{
	if (fs->list->head != NULL)
		free_token_list(fs);
}

void	free_token_list(t_fshell *fs)
{
	while (fs->list->head != NULL)
	{
		fs->list->temp = fs->list->head;
		fs->list->head = 
		
	free(fs->list->head);
	fs->list->head = NULL;
}
