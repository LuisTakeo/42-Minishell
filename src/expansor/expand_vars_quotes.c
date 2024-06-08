/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_vars_quotes.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpaim-yu <tpaim-yu@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 17:06:38 by tpaim-yu          #+#    #+#             */
/*   Updated: 2024/06/07 17:06:38 by tpaim-yu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*join_word(char *word, char *new_word)
{
	char	*temp;

	if (!word)
		return (new_word);
	temp = ft_strjoin(word, new_word);
	if (word)
		free(word);
	if (new_word)
		free(new_word);
	return (temp);
}

char	*expand_vars_and_quotes(char *word, t_minishell *minishell)
{
	char	*full_word;
	char	*temp_word;
	char	*temp;

	full_word = NULL;
	temp_word = NULL;
	temp = word;
	while (*temp)
	{
		if (*temp == '\'')
			temp_word = expand_simple_quotes(&temp);
		else if (*temp == '"')
			temp_word = expand_double_quotes(&temp, minishell);
		else if (*temp == '$')
			temp_word = expand_path(&temp, minishell);
		else
			temp_word = expand_word(&temp);
		full_word = join_word(full_word, temp_word);
		temp_word = NULL;
	}
	return (full_word);
}