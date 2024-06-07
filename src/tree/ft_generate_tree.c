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
	ft_printf("FULL WORD %s\n", temp);
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
		ft_printf("expandvarquotes->%s\n", temp);
		if (*temp == '\'')
			temp_word = expand_simple_quotes(&temp);
		if (*temp == '"')
			temp_word = expand_double_quotes(&temp, minishell);
		if (*temp == '$')
			temp_word = expand_path(&temp, minishell);
		else
			temp_word = expand_word(&temp);
		// temp_free = full_word;
		ft_printf("FULL WORD -> %s\n", temp_word);
		full_word = join_word(full_word, temp_word);
		temp_word = NULL;
	}
	ft_printf("FULL WORD %s\n", full_word);
	// quando encontrar variavel, chamar função de expandir var
	// quando encontrar "" chamar função de expandir ""
	return (full_word);
}
