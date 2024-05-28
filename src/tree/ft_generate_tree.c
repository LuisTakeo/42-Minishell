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

char	*expand_simple_quotes(char *word)
{
	char	*temp;
	int		i;

	temp = word;
	i = 0;
	if (*temp == '\'')
		temp++;
	while (temp[i] && temp[i] != '\'')
		i++;
	return (ft_substr(temp, 0, i));
}

char	*expand_word(char *word)
{
	char	*temp;
	int		i;

	temp = word;
	i = 0;
	while (temp[i] && !ft_strchr(QUOTES, temp[i]))
		i++;
	return (ft_substr(temp, 0, i));
}

char	*expand_vars_and_quotes(char *word, t_minishell *minishell)
{
	char	*full_word;
	// char	*temp;
	// int		i;

	(void)minishell;
	(void)word;
	(void)full_word;
	// quando encontrar variavel, chamar função de expandir var
	// quando encontrar '' chamar função de expandir ''
	// quando encontrar "" chamar função de expandir ""
	return (NULL);
}

// gera o argv (char **) da arvore
char	**ft_generate_argv(t_token *tokens)
{
	int		i;
	t_token	*temp;
	char	**argv;

	i = 0;
	temp = tokens;
	while (temp && temp->type == WORD)
	{
		i++;
		temp = temp->next;
	}
	argv = (char **)ft_calloc(i + 1, sizeof(char *));
	temp = tokens;
	i = 0;
	while (temp && temp->type == WORD)
	{
		argv[i] = temp->content;
		temp = temp->next;
		i++;
	}

	// se encontrar um operador redir, pular para o próximo.
	// Caso o próximo for null ou diferente de word, retornar erro
	// se encontrar um operador | ou null, alocar o char **	de acordo com os nós contados
	return (argv);
}