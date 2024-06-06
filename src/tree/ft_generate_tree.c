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
	{
		temp++;
		(*word)++;
	}
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

static char	*join_word(char **word, char **new_word)
{
	char	*temp;

	if (!*word)
		return (*new_word);
	temp = ft_strjoin(*word, *new_word);
	if (*word)
		free(*word);
	if (*new_word)
		free(*new_word);
	return (temp);
}

char	*expand_path(char **word, t_minishell *minishell)
{
	(void)minishell;
	(void)word;
	return (NULL);
}

char	*expand_double_quotes(char **word, t_minishell *minishell)
{
	char	*temp_word;
	char	*full_word;

	(void)minishell;
	temp_word = NULL;
	full_word = NULL;
	if (**word == '\"')
		(*word)++;
	while (**word && **word != '\"')
	{
		if (**word == '$')
		{
			(*word)++;
			if (ft_strchr(WHITESPACE, **word))
				temp_word = ft_strdup("$");
			else
				temp_word = expand_path(word, minishell);
		}
		else
			temp_word = expand_word(word);
		full_word = join_word(&full_word, &temp_word);
	}
	if (**word == '\"')
		(*word)++;
	return (full_word);
}

char	*expand_vars_and_quotes(char *word, t_minishell *minishell)
{
	char	*full_word;
	char	*temp_word;
	char	*temp;
	// char	*temp_free;

	(void)minishell;
	full_word = NULL;
	temp_word = NULL;
	temp = word;
	while (*temp)
	{
		if (*temp == '\'')
			temp_word = expand_simple_quotes(&temp);
		if (*temp == '"')
			temp_word = expand_double_quotes(&temp, minishell);
		else
			temp_word = expand_word(&temp);
		// temp_free = full_word;
		full_word = join_word(&full_word, &temp_word);
		temp_word = NULL;
	}
	// quando encontrar variavel, chamar função de expandir var
	// quando encontrar "" chamar função de expandir ""
	return (full_word);
}
