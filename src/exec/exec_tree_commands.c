/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_tree_commands.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpaim-yu <tpaim-yu@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 05:19:27 by tpaim-yu          #+#    #+#             */
/*   Updated: 2024/06/16 20:13:04 by tpaim-yu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	execute_single_command(t_minishell *minishell)
{
	t_command	*temp_cmd;
	int			status;

	status = 0;
	temp_cmd = minishell->tree_cmd;
	if (temp_cmd->redir)
		status = setup_redirs(temp_cmd->redir);
	if (status)
		minishell->status = status;
	else
	{
		if (!temp_cmd->argv)
			return ;
		status = is_builtin(temp_cmd->argv, minishell);
		if (status >= 0)
		{
			minishell->status = status;
			return ;
		}
		minishell->status = exec_command(temp_cmd->argv, 0, minishell);
	}
}

void	close_fds(t_minishell *minishell)
{
	t_command	*temp_tree;

	temp_tree = minishell->tree_cmd;
	while (temp_tree->type == PIPE)
	{
		close(temp_tree->fd[STDOUT_FILENO]);
		close(temp_tree->fd[STDIN_FILENO]);
		temp_tree = temp_tree->left;
	}
}

int	handle_fds(t_minishell *minishell, t_command *temp_tree, int is_left)
{
	t_command	*parent_tree;

	(void)minishell;
	parent_tree = temp_tree->parent;
	if (is_left)
		dup2(parent_tree->fd[STDOUT_FILENO], STDOUT_FILENO);
	else
	{
		dup2(parent_tree->fd[STDIN_FILENO], STDIN_FILENO);
		if (parent_tree->parent)
			dup2(parent_tree->parent->fd[1], STDOUT_FILENO);
	}
	close(parent_tree->fd[0]);
	close(parent_tree->fd[1]);
	if (temp_tree->redir && setup_redirs(temp_tree->redir))
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

void	close_all_fds(t_minishell *minishell)
{
	t_command	*temp;

	temp = minishell->tree_cmd;
	while (temp->left)
		temp = temp->left;
	close_upcoming_fds(temp);
}

void	execute_tree_commands(t_minishell *minishell)
{
	t_command	*temp_tree;
	t_list		*temp_list;
	int			status;

	status = 0;
	temp_tree = minishell->tree_cmd;
	if (temp_tree->type == WORD)
		execute_single_command(minishell);
	else
	{
		execute_pipe_command(minishell, temp_tree);
		temp_list = minishell->pid_list;
		while (temp_list)
		{
			waitpid((pid_t)((long)(temp_list->content)), &minishell->status, 0);
			minishell->status = filter_status(minishell->status);
			temp_list = temp_list->next;
		}
	}
	signal(SIGINT, &handle_signal);
}
