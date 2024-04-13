/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_token.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpaim-yu <tpaim-yu@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 08:17:13 by dde-fati          #+#    #+#             */
/*   Updated: 2024/04/12 22:41:51 by tpaim-yu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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
		while (start[i] && !ft_strchr(WHITESPACE, start[i]) && !ft_strchr(QUOTES, start[i]))
			i++;
		// verificar se há aspas -> se sim -> função para pegar conteúdo das aspas ->
		// else -> função para pegar o conteúdo do texto
		if (ft_strchr(QUOTES, start[i]))
			; //
		else if (ft_strchr(WHITESPACE, start[i])
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
	count_quotes(input);
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
