/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_tree_commands.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpaim-yu <tpaim-yu@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 05:19:27 by tpaim-yu          #+#    #+#             */
/*   Updated: 2024/06/16 14:17:47 by tpaim-yu         ###   ########.fr       */
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

void	close_upcoming_fds(t_command *parent)
{
	t_command	*parent_tree;

	parent_tree = parent->parent;
	while (parent_tree)
	{
		close(parent_tree->fd[0]);
		close(parent_tree->fd[1]);
		parent_tree = parent_tree->parent;
	}
}

void	execute_command(t_minishell *minishell, t_command *temp_tree,
	int is_left)
{
	int		status;
	pid_t	pid;
	char	*cmd;

	status = 0;
	pid = fork();
	if (pid == -1)
	{
		minishell->status = show_error("fork: ", strerror(errno), 1);
		return ;
	}
	if (!pid)
	{
		minishell->status = handle_fds(minishell, temp_tree, is_left);
		if (minishell->status || !temp_tree->argv
			|| is_builtin(temp_tree->argv, minishell) >= 0)
		{
			free_all(minishell);
			exit(minishell->status);
		}
		cmd = verify_path(temp_tree->argv[0], minishell->path);
		if (!cmd)
		{
			status = show_error(temp_tree->argv[0], ": Command not found", 127);
			close_upcoming_fds(temp_tree->parent);
			free_all(minishell);
			exit(status);
		}
		execve(cmd, temp_tree->argv, minishell->envp);
		free_all(minishell);
		close_upcoming_fds(temp_tree->parent);
		exit(EXIT_FAILURE);
	}
	ft_lstadd_back(&(minishell->pid_list), ft_lstnew((void *)((long)pid)));
}

void	execute_pipe_command(t_minishell *minishell, t_command *temp_tree)
{
	pipe(temp_tree->fd);
	(void)temp_tree;
	if (temp_tree->left && temp_tree->left->type == PIPE)
		execute_pipe_command(minishell, temp_tree->left);
	if (temp_tree->left && temp_tree->left->type != PIPE)
		execute_command(minishell, temp_tree->left, 1);
	execute_command(minishell, temp_tree->right, 0);
	close(temp_tree->fd[0]);
	close(temp_tree->fd[1]);
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
