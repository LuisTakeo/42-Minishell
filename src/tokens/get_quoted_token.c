/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_quoted_token.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dde-fati <dde-fati@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/14 18:14:23 by dde-fati          #+#    #+#             */
/*   Updated: 2024/05/21 19:19:09 by dde-fati         ###   ########.fr       */
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

void	get_quoted_token(char *input, int *i)
{
	char	quote_type;
	// int		start;

	quote_type = input[*i];
	// start = *i;
	(*i)++;
	while (input[*i] && input[*i] != quote_type)
		(*i)++;
	(*i)++;
}
