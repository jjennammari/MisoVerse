#include "../inc/miso.h"

int	main(void)
{
	t_shell	miso;

	init_variables(&miso);
	misoverse_loop(&miso);
	return (0);
}

void	init_variables(t_shell *miso)
{
	miso->exit_code = 0;
	miso->node = malloc(sizeof(t_token));
	if (!miso->node)
		return ;
	miso->node->expansion = false;
	miso->node->str = NULL;
	miso->node->next = NULL;
	miso->list.head = NULL;
	miso->list.current = NULL;
	miso->list.last_node = NULL;
}
