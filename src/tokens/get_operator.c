/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_operator.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dde-fati <dde-fati@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 17:18:32 by dde-fati          #+#    #+#             */
/*   Updated: 2024/06/02 02:44:43 by dde-fati         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	set_redir_type(t_token *tokens, char type)
{
	if (type == '<')
	{
		if (tokens && tokens->content[1] == '<')
			tokens->type = HEREDOC;
		else
			tokens->type = REDIR_IN;
	}
	else if (type == '>')
	{
		if (tokens && tokens->content[1] == '>')
			tokens->type = APPEND;
		else
			tokens->type = REDIR_OUT;
	}
}

void	set_operator_type(t_token **tokens)
{
	t_token	*aux;
	char	type;

	aux = *tokens;
	while (aux)
	{
		if (aux->type == OPERATOR)
		{
			type = aux->content[0];
			if (type == '|')
				aux->type = PIPE;
			else
				set_redir_type(aux, type);
		}
		aux = aux->next;
	}
}

static void	get_redirs_token(char *input, t_token **tokens, int *i)
{
	char	redir_type;

	redir_type = input[*i];
	if (input[*i] == redir_type)
	{
		if (input[*i + 1] == redir_type)
		{
			allocate_token(tokens, input, *i, *i + 2);
			(*i)++;
		}
		else
			allocate_token(tokens, input, *i, *i + 1);
	}
}

void	get_operator(char *input, t_token **tokens, int *i)
{
	(*tokens)->type = OPERATOR;
	if (input[*i] == '|')
		allocate_token(tokens, input, *i, *i + 1);
	else if (input[*i] == '<' || input[*i] == '>')
		get_redirs_token(input, tokens, i);
	(*i)++;
}
