/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   generate_redirs.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dde-fati <dde-fati@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/16 14:54:42 by dde-fati          #+#    #+#             */
/*   Updated: 2024/06/17 19:57:05 by dde-fati         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	reset_fds(t_minishell *minishell)
{
	if ((dup2(minishell->stdin_backup, STDIN_FILENO) < 0)
		|| (dup2(minishell->stdout_backup, STDOUT_FILENO) < 0))
	{
		perror("dup2");
		return ;
	}
}

void	add_redir(t_token **rds, t_token *new_rd, t_minishell *minishell)
{
	t_token	*temp;

	init_token(&temp);
	if (!temp)
		return ;
	(temp)->content = expand_vars_and_quotes(new_rd->next->content, minishell);
	(temp)->type = new_rd->type;
	ft_tokenadd_back(rds, temp);
}

t_token	*ft_generate_redirs(t_token **token, t_minishell *minishell)
{
	t_token	*redirs;
	t_token	*current;
	t_token	*next;

	redirs = NULL;
	current = *token;
	while (current && current->type != PIPE)
	{
		next = current->next;
		if (current->type == REDIR_IN || current->type == REDIR_OUT
			|| current->type == APPEND || current->type == HEREDOC)
			add_redir(&redirs, current, minishell);
		current = next;
	}
	return (redirs);
}
