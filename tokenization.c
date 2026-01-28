# include "parsing.h"

void	create_token_list(t_shell *miso, char *line)
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
			add_operator(miso, &line[i], &i);
		else if (ft_strchr("'", line[i]) != NULL)
		   add_argument(miso, &line[++i], &i, is_squote);
		else if (ft_strchr("\"", line[i]) != NULL)
		   add_argument(miso, &line[++i], &i, is_dquote);
		else
			add_argument(miso, &line[i], &i, is_whitespace);
	}
}

void	add_operator(t_shell *miso, char *line, int *pi)
{
	if (line[*pi] == '|')
	{
		create_new_node(miso, "|", PIPE);
		*pi += 1;
	}
	else if (line[*pi] == '<' || line[*pi] == '>')
		  add_redirection(miso, &line[*pi], pi);
}

void	add_redirection(t_shell *miso, char *line, int *pi)
{
	if (line[*pi] == '<')
	{
		if (line[*pi++] == '<')
		{
			create_new_node(miso, "<<", HEREDOC);
			*pi += 1;
		}
		else
			create_new_node(miso, "<", RD_IN);
	}
	else if (line[*pi] == '<')
	{
		if (line[*pi++] == '<')
		{
			create_new_node(miso, "<<", HEREDOC);
			*pi += 1;
		}
		else
			create_new_node(miso, "<", RD_IN);
	}
	*pi += 1;
}

void	add_argument(t_shell *miso, char *line, int *pi, int (*f)(char))
{
	char	*temp;

	temp = NULL;
	while (line[*pi])
	{
		if ((*f)(line[*pi]))
			break ;
		else if (line[*pi] == '$')
			miso->node->expand = true;
		temp[*pi] = line[*pi];
		pi++;
	}
//	if (!(*f)(line[*pi]))
//		print syntax error
	create_new_node(miso, temp, ARG);
}
