/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_token_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpaim-yu <tpaim-yu@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 09:51:40 by dde-fati          #+#    #+#             */
/*   Updated: 2024/06/03 17:14:23 by tpaim-yu         ###   ########.fr       */
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
			if(aux->content[0] == '|')
				ft_fdprintf("minishell: syntax error near unexpected token `%s'\n", STDERR_FILENO, aux->content);
			else if (aux->next && aux->next->next)
				ft_fdprintf("minishell: syntax error near "
					"unexpected token `%s'\n",
					STDERR_FILENO, aux->next->content);
			if (aux->next && aux->next->next)
				ft_fdprintf("minishell: syntax error near unexpected token `%s'\n", STDERR_FILENO, aux->next->content);
			else
				ft_fdprintf("minishell: syntax error near unexpected token `newline'\n", STDERR_FILENO);
			return (EXIT_FAILURE);
		}
		aux = aux->next;
	}
	return (EXIT_SUCCESS);
}
