/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_generate_tree.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpaim-yu <tpaim-yu@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 18:41:38 by tpaim-yu          #+#    #+#             */
/*   Updated: 2024/05/21 18:41:38 by tpaim-yu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*expand_simple_quotes(char **word)
{
	char	*temp;
	int		i;

	temp = *word;
	i = 0;
	if (*temp == '\'')
		(temp++, (*word)++);
	while (temp[i] && temp[i] != '\'')
		i++;
	*word += i + 1;
	return (ft_substr(temp, 0, i));
}

char	*expand_word(char **word)
{
	char	*temp;
	int		i;

	temp = *word;
	i = 0;
	while (temp[i] && !ft_strchr(QUOTES, temp[i]))
		i++;
	*word += i;
	return (ft_substr(temp, 0, i));
}

static char	*join_word(char *word, char *new_word)
{
	char	*temp;

	if (!word)
		return (ft_strdup(new_word));
	temp = word;
	word = ft_strjoin(word, new_word);
	free(temp);
	return (word);
}

char	*expand_vars_and_quotes(char *word, t_minishell *minishell)
{
	char	*full_word;
	char	*temp_word;
	char	*temp;

	(void)minishell;
	full_word = NULL;
	temp_word = NULL;
	temp = word;
	while (*temp)
	{
		if (*temp == '\'')
			temp_word = expand_simple_quotes(&temp);
		else
			temp_word = expand_word(&temp);
		full_word = join_word(full_word, temp_word);
		if (temp_word)
			free(temp_word);
		temp_word = NULL;
	}
	// quando encontrar variavel, chamar função de expandir var
	// quando encontrar "" chamar função de expandir ""
	return (full_word);
}
