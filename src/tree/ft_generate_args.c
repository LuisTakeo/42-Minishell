/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_generate_args.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpaim-yu <tpaim-yu@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 14:36:36 by tpaim-yu          #+#    #+#             */
/*   Updated: 2024/05/31 14:36:36 by tpaim-yu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// gera o argv (char **) da arvore
char	**ft_generate_argv(t_token *tokens, t_minishell *minishell)
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
		argv[i] = expand_vars_and_quotes(temp->content, minishell);
		temp = temp->next;
		i++;
	}

	// se encontrar um operador redir, pular para o próximo.
	// Caso o próximo for null ou diferente de word, retornar erro
	// se encontrar um operador | ou null, alocar o char **	de acordo com os nós contados
	return (argv);
}
