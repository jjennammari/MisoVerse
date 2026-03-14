/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miso_tokenize.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jemustaj <jemustaj@student.42Porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/29 22:47:33 by jemustaj          #+#    #+#             */
/*   Updated: 2026/03/08 22:22:13 by lde-san-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/miso.h"

void	miso_tokenize(t_shell *miso, char *line);
void	miso_tokenize_operators(t_shell *miso, char *str, int *pi);
void	miso_tokenize_redirections(t_shell *miso, char *str, int *pi);
void	miso_tokenize_quotes(t_shell *miso, char *str, int *pi);
//void	miso_tokenize_arguments(t_shell *miso, char *str, int *pi);

void	miso_tokenize(t_shell *miso, char *line)
{
	int		i;

	i = 0;
	while (line[i])
	{
		while (line[i] && miso_is_whitespace(line[i]))
			i++;
		if (ft_strchr("<|>", line[i]))
			miso_tokenize_operators(miso, &line[i], &i);
		else if (ft_strchr("'\"", line[i]) != NULL)
		{
			miso->node->quotes = 1;
			miso_tokenize_quotes(miso, &line[i], &i);
		}
		else
			miso_tokenize_quotes(miso, &line[i], &i);//NOTE: testing if quotes and args work with same function, change name back
	}
}

void	miso_tokenize_operators(t_shell *miso, char *line, int *pi)
{
	int	i;

	i = 0;
	if (line[i] == '|')
	{
		miso_build_token_list(miso, ft_strdup("|"), PIPE);
		*pi += 1;
	}
	else
		miso_tokenize_redirections(miso, line, pi);
}

void	miso_tokenize_redirections(t_shell *miso, char *line, int *pi)
{
	int	i;

	i = 0;
	if (line[i] == '<')
	{
		if (line[i + 1] == '<')
		{
			miso_build_token_list(miso, ft_strdup("<<"), HEREDOC);
			miso->list.hd_count += 1;
			*pi += 1;
		}
		else
			miso_build_token_list(miso, ft_strdup("<"), RD_IN);
	}
	else if (line[i] == '>')
	{
		if (line[i + 1] == '>')
		{
			miso_build_token_list(miso, ft_strdup(">>"), APPEND);
			*pi += 1;
		}
		else
			miso_build_token_list(miso, ft_strdup(">"), RD_OUT);
	}
	*pi += 1;
}

void	miso_tokenize_quotes(t_shell *miso, char *line, int *pi)
{
	char	*str;
	int		i;

//	miso->node->quotes = 1;NOTE: testing if quotes AND args work in same function
	str = miso_allocate_str(miso, 1);
	i = 0;
	while (line[i] && !miso_is_whitespace(line[i]))
	{
		miso_update_quotes(miso, line[i]);
		if (miso->node->quotes == 0 && ft_strchr("<|>'\"", line[i]))
			break ;
		if (miso->node->quotes == 1 && ft_strchr("'\"", line[i]) && ft_strchr("'\"", line[i + 1]) && miso_skip_empty_quotes(miso, &line[i], &i))
			continue ;
		if (line[i] == '$' && miso->node->expand == 0)
			miso->node->expand = 1;
		str = miso_add_char_to_str(miso, str, line[i]);
		i++;
	}
	miso_build_token_list(miso, str, ARG);
	*pi += i;
}//NOTE:testing if quotes and args work with same function

/*void	miso_tokenize_arguments(t_shell *miso, char *str, int *pi)
{
	char	*temp;
	int		len;

	len = 0;
	while (str[len] && !miso_is_whitespace(str[len]) && !ft_strchr("<|>'\"", str[len]))
	{
		if (str[len] == '$' && miso->node->expand == 0)
			miso->node->expand = 1;
		len++;
	}
	temp = ft_substr(str, 0, len);
	miso_build_token_list(miso, temp, ARG);
	*pi += len;
}*/
