/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builds.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpaim-yu <tpaim-yu@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/16 14:23:54 by tpaim-yu          #+#    #+#             */
/*   Updated: 2024/06/16 14:23:54 by tpaim-yu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	build_commands(t_minishell *minishell)
{
	int	status;

	get_token(minishell->input, &(minishell->tokens));
	if (!(minishell->tokens) || !(minishell->tokens->content)
		|| validate_tokens(minishell->tokens) == 1)
		return (EXIT_FAILURE);
	set_operator_type(&(minishell->tokens));
	status = verify_heredoc(minishell);
	if (status)
	{
		minishell->status = status;
		return (EXIT_FAILURE);
	}
	ft_generate_tree(minishell);
	return (EXIT_SUCCESS);
}

void	build_and_execute(t_minishell *minishell)
{
	add_history(minishell->input);
	if (build_commands(minishell))
	{
		free_resources_prompt(minishell);
		return ;
	}
	execute_tree_commands(minishell);
	free_resources_prompt(minishell);
}
