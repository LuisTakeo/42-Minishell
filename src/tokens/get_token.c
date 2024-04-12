/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_token.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dde-fati <dde-fati@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 08:17:13 by dde-fati          #+#    #+#             */
/*   Updated: 2024/04/12 19:19:36 by dde-fati         ###   ########.fr       */
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

static void	split_tokens(char *input, t_token **tokens)
{
	t_token	*aux;
	char	*start;
	int		i;

	aux = *tokens;
	start = input;
	i = 0;
	while (start[i])
	{
		while (start[i] && ft_strchr(WHITESPACE, start[i]))
			i++;
		start += i;
		i = 0;
		while (start[i] && !ft_strchr(WHITESPACE, start[i]))
			i++;
		if (ft_strchr(WHITESPACE, start[i])
			&& !ft_strchr(WHITESPACE, start[i - 1]) && i != 0)
		{
			aux->content = ft_substr(start, 0, i);
			init_token(&aux->next);
			aux = aux->next;
			start += i;
			i = 0;
		}
		i++;
	}
}

void	get_token(char *input, t_token **tokens)
{
	t_token	*aux;
	int		i;

	if (!input[0])
		return ;
	init_token(tokens);
	split_tokens(input, tokens);

	// Validando lista de tokens
	i = 1;
	aux = *tokens;
	while (aux)
	{
		printf("Token[%d]: %s!\n", i, aux->content);
		aux = aux->next;
		i++;
	}
}
