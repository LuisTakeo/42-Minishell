/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_special_token.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dde-fati <dde-fati@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 17:18:32 by dde-fati          #+#    #+#             */
/*   Updated: 2024/04/19 21:01:44 by dde-fati         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	get_pipe_token(char *input, t_token **tokens, int *i)
{
	(*tokens)->type = PIPE;
	allocate_token(tokens, input, *i, *i + 1);
}

static void	set_redirs_type(t_token **tokens, char type, int is_double)
{
	if (type == '<')
	{
		if (is_double)
			(*tokens)->type = HEREDOC;
		else
			(*tokens)->type = REDIR_IN;
	}
	else
	{
		if (is_double)
			(*tokens)->type = APPEND;
		else
			(*tokens)->type = REDIR_OUT;
	}
}

static void	get_redirs_token(char *input, t_token **tokens, int *i)
{
	char	redir_type;
	int		is_double;
	t_token	*aux;

	redir_type = input[*i];
	is_double = 0;
	aux = *tokens;
	if (input[*i] == redir_type)
	{
		if (input[*i + 1] == redir_type)
		{
			allocate_token(tokens, input, *i, *i + 2);
			is_double = 1;
			(*i)++;
		}
		else
			allocate_token(tokens, input, *i, *i + 1);
	}
	set_redirs_type(&aux, redir_type, is_double);
}

void	get_special_token(char *input, t_token **tokens, int *i)
{
	if (input[*i] == '|')
		get_pipe_token(input, tokens, i);
	else if (input[*i] == '<' || input[*i] == '>')
		get_redirs_token(input, tokens, i);
	(*i)++;
}
