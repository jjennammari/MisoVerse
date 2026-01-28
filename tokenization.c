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
		else if (line[i] == '\'')
		   add_argument(miso, &line[++i], &i, is_squote);
		else if (line[i] == '"')
		   add_argument(miso, &line[++i], &i, is_dquote);
		else
			add_argument(miso, &line[i], &i, is_whitespace);
	}
}

void	add_operator(t_shell *miso, char *line, int *pi)
{
	if (line[*pi] == '|')
	{
		add_to_list(miso, "|", PIPE);
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
			add_to_list(miso, "<<", HEREDOC);
			*pi += 1;
		}
		else
			add_to_list(miso, "<", RD_IN);
	}
	else if (line[*pi] == '<')
	{
		if (line[*pi++] == '<')
		{
			add_to_list(miso, "<<", HEREDOC);
			*pi += 1;
		}
		else
			add_to_list(miso, "<", RD_IN);
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
	add_to_list(miso, temp, ARG);
}

void	add_to_list(t_shell *miso, char *str, t_token_type type)
{
	t_token	*new_node;

	new_node = malloc(sizeof(t_token));
	if (!new_node)
		// free linked list
		return ;
	if (miso->list.head == NULL)
		miso->list.head = new_node;
	
}
