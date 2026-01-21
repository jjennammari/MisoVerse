# include "parsing.h"

int	create_token_list(t_miso *mv, char *line)
{
	t_line	*list;
	int		i;

	list = malloc(sizeof(t_line));
	if (!list)
		exit_program(mv);
	i = 0;
	while (line[i])
	{
		if (is_whitespace(line[i]))
			i++;
		else if (is_operator(line[i]))
			add_operator(list, &line[i], &i);
		else if (is_bltin(line[i]))
			add_bltin(list);
		else
			add_arg(list);
	}
	return (0);
}

void	add_operator(t_line *list, char *line, int *p_i)
{
	if (*line == '|')
	{
		add_new_node(list, '|', PIPE);
		p_i++;
		return ;
	}
}

void	add_new_node(t_line *list, t_token *str, t_token_type type)
