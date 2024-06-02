/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_token.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dde-fati <dde-fati@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 08:17:13 by dde-fati          #+#    #+#             */
/*   Updated: 2024/06/02 02:31:53 by dde-fati         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	get_word(char *input, t_token **tokens, int *i)
{
	int	start;

	(*tokens)->type = WORD;
	start = *i;
	while (input[*i] && !ft_strchr(WHITESPACE, input[*i])
		&& !ft_strchr(SYMBOLS, input[*i]))
	{
		while (input[*i] && !ft_strchr(WHITESPACE, input[*i])
			&& !ft_strchr(QUOTES, input[*i]) && !ft_strchr(SYMBOLS, input[*i]))
			(*i)++;
		if (input[*i] && ft_strchr(QUOTES, input[*i]))
			get_quoted_token(input, i);
	}
	if (*i > start)
		allocate_token(tokens, input, start, *i);
}

static void	split_tokens(char *input, t_token **tokens)
{
	t_token	*aux;
	int		i;

	aux = *tokens;
	i = 0;
	while (input[i])
	{
		skip_whitespace(input, &i);
		if (input[i] && ft_strchr(SYMBOLS, input[i]))
			get_operator(input, &aux, &i);
		else if (input[i])
			get_word(input, &aux, &i);
	}
}

static void	verify_null(t_token **tokens)
{
	t_token	*prev;
	t_token	*temp;

	if (!(*tokens))
		return ;
	temp = *tokens;
	prev = NULL;
	while (temp)
	{
		if (!temp->content && !prev)
		{
			prev = temp;
			temp = temp->next;
			free_token(&prev);
		}
		else if (!temp->content)
		{
			temp = temp->next;
			free_token(&(prev->next));
			prev->next = temp;
			temp = prev;
		}
		prev = temp;
		temp = temp->next;
	}
}

// Função teste pra imprimir os tokens
void	print_tokens(t_token *tokens)
{
	t_token	*aux;
	int		i;

	aux = tokens;
	i = 1;
	while (aux)
	{
		ft_printf("Token[%d]: %s!\n ", i, aux->content);
		ft_printf("Type[%d]: %i!\n\n", i, aux->type);
		aux = aux->next;
		i++;
	}
}

void	get_token(char *input, t_token **tokens)
{
	if (!input || !input[0])
		return ;
	count_quotes(input);
	init_token(tokens);
	split_tokens(input, tokens);
	verify_null(tokens);
}
