/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_token_utils2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dde-fati <dde-fati@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/16 15:10:01 by dde-fati          #+#    #+#             */
/*   Updated: 2024/06/16 15:10:40 by dde-fati         ###   ########.fr       */
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
