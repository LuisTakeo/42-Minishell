/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_token.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dde-fati <dde-fati@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 08:17:13 by dde-fati          #+#    #+#             */
/*   Updated: 2024/04/25 14:05:52 by dde-fati         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	get_word_token(char *input, t_token **tokens, int *i)
{
	int	start;

	start = *i;
	if (input[*i] && !ft_strchr(WHITESPACE, input[*i])
		&& !ft_strchr(QUOTES, input[*i]) && !ft_strchr(SYMBOLS, input[*i]))
	{
		while (input[*i] && !ft_strchr(WHITESPACE, input[*i])
			&& !ft_strchr(QUOTES, input[*i]) && !ft_strchr(SYMBOLS, input[*i]))
			(*i)++;
	}
	if (*i > start)
		allocate_token(tokens, input, start, *i);
}

void	get_env_token(char *input, t_token **tokens, int *i)
{
	int	start;

	start = *i;
	(*i)++;
	(*tokens)->type = ENV;
	if (input[*i] && input[*i] == '?')
	{
		(*tokens)->type = STATUS;
		(*i)++;
	}
	else
	{
		while (input[*i] && !ft_strchr(WHITESPACE, input[*i])
			&& !ft_strchr(QUOTES, input[*i])
			&& !ft_strchr(SYMBOLS, input[*i]))
			(*i)++;
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
		if (ft_strchr(SYMBOLS, input[i]))
			get_special_token(input, &aux, &i);
		else if (ft_strchr(QUOTES, input[i]))
			get_quoted_token(input, &aux, &i);
		else if (input[i] == '$')
			get_env_token(input, &aux, &i);
		else
			get_word_token(input, &aux, &i);
	}
}

void	get_token(char *input, t_token **tokens)
{
	t_token	*aux;
	int		i;

	if (!input[0])
		return ;
	count_quotes(input);
	init_token(tokens);
	split_tokens(input, tokens);

	i = 1;
	aux = *tokens;
	while (aux)
	{
		ft_printf("Token[%d]: %s!\n ", i, aux->content);
		ft_printf("Type[%d]: %i!\n\n", i, aux->type);
		aux = aux->next;
		i++;
	}
}
