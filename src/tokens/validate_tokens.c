/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_tokens.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpaim-yu <tpaim-yu@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/16 15:10:01 by dde-fati          #+#    #+#             */
/*   Updated: 2024/06/27 12:16:52 by tpaim-yu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	return_validation_tokens(t_token *tokens)
{
	if (tokens->content[0] == '|' && (!tokens->next
			|| (tokens->next && tokens->next->content[0] == '|')))
		return (show_error("minishell: "
				"syntax error near unexpected token ",
				tokens->content, 1));
	else if (tokens->content[0] != '|' && tokens->next)
		return (show_error("minishell: "
				"syntax error near unexpected token ",
				tokens->next->content, 1));
	else if (tokens->content[0] != '|')
		return (show_error("minishell: "
				"syntax error near unexpected token ",
				"`newline'", 1));
	return (0);
}

int	validate_tokens(t_token *tokens)
{
	t_token	*aux;

	aux = tokens;
	if (aux && aux->type == OPERATOR && aux->content[0] == '|')
		return (show_error("minishell: "
				"syntax error near unexpected token ",
				aux->content, 1));
	while (aux)
	{
		if (aux->type == OPERATOR && (aux->next == NULL
				|| aux->next->type == OPERATOR))
		{
			if (return_validation_tokens(aux))
				return (1);
		}
		aux = aux->next;
	}
	return (EXIT_SUCCESS);
}
