/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_token_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dde-fati <dde-fati@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 09:51:40 by dde-fati          #+#    #+#             */
/*   Updated: 2024/06/08 17:29:59 by dde-fati         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	init_token(t_token **tokens)
{
	*tokens = (t_token *)malloc(sizeof(t_token));
	if (!(*tokens))
		return ;
	(*tokens)->type = -1;
	(*tokens)->content = NULL;
	(*tokens)->next = NULL;
	(*tokens)->prev = NULL;
}

void	allocate_token(t_token **tokens, char *input, int start, int end)
{
	(*tokens)->content = ft_substr(input, start, end - start);
	if (input[end] != '\0')
	{
		if ((*tokens)->next == NULL)
		{
			init_token(&(*tokens)->next);
			(*tokens)->next->prev = *tokens;
		}
		*tokens = (*tokens)->next;
	}
}

void	free_token(t_token **tokens)
{
	t_token	*aux;

	while (*tokens)
	{
		aux = *tokens;
		*tokens = (*tokens)->next;
		if (aux->content)
			free(aux->content);
		free(aux);
	}
	free(*tokens);
}

void	skip_whitespace(char *input, int *i)
{
	while (input[*i] && ft_strchr(WHITESPACE, input[*i]))
		(*i)++;
}

int	validate_tokens(t_token *tokens)
{
	t_token	*aux;

	aux = tokens;
	while (aux)
	{
		if (aux->type == OPERATOR && (aux->next == NULL
				|| aux->next->type == OPERATOR))
		{
			if (aux->content[0] == '|' && (!aux->next
					|| (aux->next && aux->next->content[0] == '|')))
				return (show_error("minishell: "
						"syntax error near unexpected token ",
						aux->content, 1));
			else if (aux->content[0] != '|' && aux->next)
				return (show_error("minishell: "
						"syntax error near unexpected token ",
						aux->next->content, 1));
			else
				return (show_error("minishell: "
						"syntax error near unexpected token ",
						"`newline'", 1));
		}
		aux = aux->next;
	}
	return (EXIT_SUCCESS);
}
