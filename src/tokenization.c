# include "../inc/miso.h"

void	create_token_list(t_miso *mv, char *line)
{
	t_line	*list;
	int		i;

	list = malloc(sizeof(t_line));
	if (!list)
		return ;
	i = 0;
	while (line[i])
	{
		while (line[i] && is_whitespace(line[i]))
			i++;
		if (ft_strchr("<|>", line[i]) != NULL)
			add_operator(list, &line[i], &i);
		else if (ft_strchr('\'', line[i] != NULL)
		   add_argument(list, &line[i], &i, &is_squote());
		else if (ft_strchr('\"', line[i] != NULL)
		   add_argument(list, &line[i], &i, &is_dquote());
		else
			add_argument(list, &line[i], &i, &is_whiteshpace());
	}
}

void	add_operator(t_line *list, char *line, int *pi)
{
	if (line[*pi] == '|')
	{
		add_new_token(list, '|', PIPE);
		*pi += 1;
	}
	else if (line[*pi] == '<' || line[*pi] == '>')
		  add_redirection(list, &line[*pi], pi);
}

void	add_redirection(t_line *list, char *line, int *pi)
{
	if (line[*pi] == '<')
	{
		if (line[*pi++] == '<')
		{
			add_new_token(list, '<<', HEREDOC);
			*pi += 1;
		}
		else
			add_new_token(list, '<', RD_IN);
	}
	else if (line[*pi] == '<')
	{
		if (line[*pi++] == '<')
		{
			add_new_token(list, '<<', HEREDOC);
			*pi += 1;
		}
		else
			add_new_token(list, '<', RD_IN);
	}
	*pi += 1;
}

void	add_argument(t_line *list, char *line, int *pi, *f(char *))
{
	if (ft_strchr("\"\'", line[*pi]))
		add_quotes(list, &line[*pi], pi);
}
