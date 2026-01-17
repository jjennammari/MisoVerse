#include "parsing.h"

int	main(void)
{
	t_line	*list;

	init_variables(&list);
	fastshell_jenna(&list);
	free(list);
}

void	init_variables(t_line **list)
{
	*list = malloc(sizeof(t_line));
	if (!list)
		return ;
	(*list)->node.token_str = NULL;
	(*list)->node.next = NULL;
	(*list)->node.index = 0;
	(*list)->head = NULL;
	(*list)->current = NULL;
}
