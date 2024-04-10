/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_token.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dde-fati <dde-fati@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 08:17:13 by dde-fati          #+#    #+#             */
/*   Updated: 2024/04/10 09:49:46 by dde-fati         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	init_token(t_token **tokens)
{
	*tokens = (t_token *)malloc(sizeof(t_token));
	if (!(*tokens))
		return ;
	(*tokens)->type = -1;
	(*tokens)->content = NULL;
	(*tokens)->next = NULL;
}

static t_token	*split_tokens(char *input, t_token *tokens)
{
	t_token	*head;
	char	*start;
	int		i;

	head = tokens;
	start = input;
	i = 0;
	while (start[i])
	{
		if (ft_strchr(WHITESPACE, start[i])
			&& !ft_strchr(WHITESPACE, start[i + 1]) && i != 0)
		{
			tokens->content = ft_substr(start, 0, i);
			init_token(&tokens->next);
			tokens = tokens->next;
			start += (i + 1);
			i = 0;
		}
		i++;
	}
	tokens->content = ft_substr(start, 0, i);
	tokens->next = NULL;
	return (head);
}

void	get_token(char *input, t_token **tokens)
{
	t_token	*aux;
	int		i;

	init_token(tokens);
	*tokens = split_tokens(input, *tokens);

	// Validando lista de tokens
	i = 1;
	aux = *tokens;
	while (aux)
	{
		printf("Token[%d]: %s\n", i, aux->content);
		aux = aux->next;
		i++;
	}
}
