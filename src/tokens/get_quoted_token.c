/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_quoted_token.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpaim-yu <tpaim-yu@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/14 18:14:23 by dde-fati          #+#    #+#             */
/*   Updated: 2024/04/24 20:59:48 by tpaim-yu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	count_quotes(char *input)
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
	if (occ_s_quote % 2 == 0 && occ_d_quote % 2 == 0)
		return (0);
	return (1);
}

void	get_quoted_token(char *input, t_token **tokens, int *i)
{
	char	quote_type;
	int		start;

	quote_type = input[*i];
	start = *i;
	(*i)++;
	while (input[*i] && input[*i] != quote_type)
		(*i)++;
	if (input[*i] == quote_type)
		allocate_token(tokens, input, start, *i + 1);
	(*i)++;
}
