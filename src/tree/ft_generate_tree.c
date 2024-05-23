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

char	*expand_vars_and_quotes(char *word, t_minishell *minishell)
{
	(void)word;
	(void)minishell;
	return (NULL);
}

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