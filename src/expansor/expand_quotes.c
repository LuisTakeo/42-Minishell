/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpaim-yu <tpaim-yu@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 21:37:33 by tpaim-yu          #+#    #+#             */
/*   Updated: 2024/06/06 21:37:33 by tpaim-yu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*expand_simple_quotes(char **word)
{
	char	*temp;
	int		i;

	temp = *word;
	i = -1;
	if (*temp == '\'')
	{
		temp++;
		(*word)++;
	}
	while (temp[++i] && temp[i] != '\'')
		(*word)++;
	(*word)++;
	return (ft_substr(temp, 0, i));
}

char	*expand_double_quotes(char **word, t_minishell *minishell)
{
	char	*temp_word;
	char	*full_word;

	temp_word = NULL;
	full_word = NULL;
	if (**word == '\"')
		(*word)++;
	if (**word == '\"')
	{
		(*word)++;
		return (ft_strdup(""));
	}
	while (**word && **word != '\"')
	{
		if (**word == '$')
				temp_word = expand_path(&(*word), minishell);
		else
			temp_word = expand_word(&(*word));
		full_word = join_word(full_word, temp_word);
	}
	(*word)++;
	return (full_word);
}
