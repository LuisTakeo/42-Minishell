/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_token.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dde-fati <dde-fati@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 08:17:13 by dde-fati          #+#    #+#             */
/*   Updated: 2024/04/14 17:32:53 by dde-fati         ###   ########.fr       */
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

static int	count_quotes(char *input)
{
	int	i;
	int	occ_s_quote;
	int	occ_d_quote;

	i = 0;
	occ_s_quote = 0;
	occ_d_quote = 0;
	while (input[i])
	{
		if (input[i] == '"')
		{
			occ_d_quote++;
			i++;
			while (input[i] && input[i] != '"')
				i++;
			if (input[i++] == '"')
				occ_d_quote++;
			continue ;
		}
		if (input[i] == '\'')
		{
			occ_s_quote++;
			i++;
			while (input[i] && input[i] != '\'')
				i++;
			if (input[i++] == '\'')
				occ_s_quote++;
			continue ;
		}
		i++;
	}
	ft_printf("Quotes: single %d double %d\n", occ_s_quote, occ_d_quote);
	if (occ_s_quote % 2 == 0 && occ_d_quote % 2 == 0)
		return (0);
	return (1);
}

static void	get_quoted_tokens(char *input, t_token **tokens, int *i)
{
	char	quote_type;
	int		start;

	quote_type = input[*i];
	start = *i;
	(*i)++;
	while (input[*i] && input[*i] != quote_type)
		(*i)++;
	if (input[*i] == quote_type)
	{
		(*tokens)->content = ft_substr(input, start, *i - start + 1);
		if (input[*i + 1] != '\0')
		{
			init_token(&(*tokens)->next);
			*tokens = (*tokens)->next;
		}
	}
}

static void	skip_whitespace(char *input, int *i)
{
	while (input[*i] && ft_strchr(WHITESPACE, input[*i]))
		(*i)++;
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
		skip_whitespace(start, &i);
		start += i;
		i = 0;
		if (start[i] && !ft_strchr(WHITESPACE, start[i])
			&& !ft_strchr(QUOTES, start[i]))
		{
			while (start[i] && !ft_strchr(WHITESPACE, start[i])
				&& !ft_strchr(QUOTES, start[i]))
				i++;
			if (ft_strchr(WHITESPACE, start[i])
				&& !ft_strchr(WHITESPACE, start[i - 1]) && i != 0)
			{
				aux->content = ft_substr(start, 0, i);
				if (start[i + 1] != '\0')
				{
					init_token(&aux->next);
					aux = aux->next;
				}
				start += i;
				i = 0;
			}
		}
		else if (start[i] && ft_strchr(QUOTES, start[i]))
		{
			get_quoted_tokens(start, &aux, &i);
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
	count_quotes(input);
	init_token(tokens);
	split_tokens(input, tokens);

	i = 1;
	aux = *tokens;
	while (aux)
	{
		printf("Token[%d]: %s!\n", i, aux->content);
		aux = aux->next;
		i++;
	}
}
