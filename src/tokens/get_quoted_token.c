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

int	count_type_quote(char quote, int i, char *input)
{
	if (input[i] && input[i] == quote)
	{
		i++;
		while (input[i] && input[i] != quote)
			i++;
		if (!input[i])
			return (-1);
	}
	return (++i);
}

int	count_quotes(char *input)
{
	int	i;

	i = 0;
	while (input[i])
	{
		if (ft_strchr(QUOTES, input[i]))
		{
			if (input[i] == '"')
				i = count_type_quote('"', i, input);
			else
				i = count_type_quote('\'', i, input);
			if (i < 0)
				return (show_error("minishell: ",
						"You need to close your quotes!!!", 1));
		}
		else
			i++;
	}
	return (0);
}

void	get_quoted_token(char *input, int *i)
{
	char	quote_type;

	quote_type = input[*i];
	(*i)++;
	while (input[*i] && input[*i] != quote_type)
		(*i)++;
	(*i)++;
}
