/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_multiple.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpaim-yu <tpaim-yu@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/16 15:07:06 by tpaim-yu          #+#    #+#             */
/*   Updated: 2024/06/16 15:07:06 by tpaim-yu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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

char	*define_full_path(char *cmd, char **path)
{
	char	*full_path;

	if (verify_abs_path(cmd))
		return (cmd);
	full_path = verify_path(cmd, path);
	return (full_path);
}

void	child_process(t_minishell *minishell, t_command *temp_tree,
	int is_left)
{
	char	*cmd;
	int		status;

	status = 0;
	minishell->status = handle_fds(minishell, temp_tree, is_left);
	if (minishell->status || !temp_tree->argv)
		free_child(minishell);
	status = is_builtin(temp_tree->argv, minishell);
	if (status >= 0)
	{
		minishell->status = status;
		free_child(minishell);
	}
	cmd = define_full_path(temp_tree->argv[0], minishell->path);
	if (!cmd)
	{
		minishell->status = show_error(temp_tree->argv[0], ": Command not found", 127);
		close_upcoming_fds(temp_tree);
		free_child(minishell);
	}
	execve(cmd, temp_tree->argv, minishell->envp);
	free_all(minishell);
	exit(EXIT_FAILURE);
}

void	execute_command(t_minishell *minishell, t_command *temp_tree,
	int is_left)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
	{
		minishell->status = show_error("fork: ", strerror(errno), 1);
		return ;
	}
	if (!pid)
		child_process(minishell, temp_tree, is_left);
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
