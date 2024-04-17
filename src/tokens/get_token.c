/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_token.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dde-fati <dde-fati@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 08:17:13 by dde-fati          #+#    #+#             */
/*   Updated: 2024/04/17 19:21:21 by dde-fati         ###   ########.fr       */
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

void	allocate_token(t_token **tokens, char *input, int start, int end)
{
	(*tokens)->content = ft_substr(input, start, end - start);
	if (input[end + 1] != '\0')
	{
		init_token(&(*tokens)->next);
		*tokens = (*tokens)->next;
	}
}

static void	skip_whitespace(char *input, int *i)
{
	while (input[*i] && ft_strchr(WHITESPACE, input[*i]))
		(*i)++;
}

/*static void	split_tokens(char *input, t_token **tokens)
{
	t_token	*aux;
	char	*start;
	int		i;

	aux = *tokens;
	start = input;
	i = 0;
	while (start[i])
	{
		skip_whitespace(start, &i);
		start += i;
		i = 0;
		if (start[i] && !ft_strchr(WHITESPACE, start[i])
			&& !ft_strchr(QUOTES, start[i]))
		{
			while (start[i] && !ft_strchr(WHITESPACE, start[i])
				&& !ft_strchr(QUOTES, start[i]))
				i++;
			if (i != 0)
			{
				allocate_token(&aux, start, 0, i);
				start += i;
				i = 0;
			}
		}
		else if (start[i] && ft_strchr(QUOTES, start[i]))
		{
			get_quoted_token(&aux, start, &i);
			start += i + 1;
			i = 0;
		}
		else
			i++;
	}
}*/

static void	split_tokens(char *input, t_token **tokens)
{
	t_token	*aux;
	t_token	*tmp;

	aux = NULL;
	while (*input)
	{
		skip_whitespace(&input);
		if (is_special_symbol(*input))
			get_special_token(&input, &aux);
		else if (*input == '\'' || *input == '\"')
			get_quoted_token(&input, &aux);
		else if (*input == '$')
			expand_variable(&input, &aux);
		else
			get_word_token(&input, &aux);
		if (aux)
		{
			if (!*tokens)
				*tokens = aux; // Primeiro token
			else
			{
				tmp = *tokens;
				while (tmp->next)
					tmp = tmp->next;
				tmp->next = aux;  // Encadear ao último token
			}
			aux = NULL;
		}
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
		ft_printf("Token[%d]: %s!\n", i, aux->content);
		aux = aux->next;
		i++;
	}
}
