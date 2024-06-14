#include "../includes/minishell.h"

void	execute_single_command(t_minishell *minishell)
{
	t_command	*temp_cmd;
	int			status;

	temp_cmd = minishell->tree_cmd;
	// necessário adaptar execução dos builtins em caso de redirs
	// leaks na execução de bultins com redirects
	// echo entrando em loop infinito com >
	status = is_builtin(temp_cmd->argv, minishell);
	if (status >= 0)
	{
		minishell->status = status;
		return ;
	}
	if (temp_cmd->redir)
		minishell->status = exec_command(temp_cmd->argv, temp_cmd->redir->file_fd, minishell);
	else
		minishell->status = exec_command(temp_cmd->argv, 0, minishell);
	// ft_printf("Status: %d\n", minishell->status);
	// minishell->status = (minishell->status >> 8) & 0xff;
	// ft_printf("Status: %d\n", minishell->status);
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

void	execute_command(t_minishell *minishell, t_command *temp_tree,
	int is_left)
{
	int		status;
	pid_t	pid;
	char	*cmd;
	t_command	*parent_tree;

	status = 0;
	parent_tree = temp_tree->parent;
	(void)is_left;
	pid = fork();
	if (pid == -1)
	{
		minishell->status = show_error("fork: ", strerror(errno), 1);
		return ;
	}
	if (!pid)
	{
		ft_printf("%s\n", temp_tree->argv[0]);
		// if	(is_left)
		// {

		// 	dup2(parent_tree->fd[STDOUT_FILENO], STDOUT_FILENO);
		// }
		// else
		// {
		// 	dup2(parent_tree->fd[STDIN_FILENO], STDIN_FILENO);
		// 	dup2(STDOUT_FILENO, STDOUT_FILENO);
		// }
		(void)parent_tree;
        if (is_builtin(temp_tree->argv, minishell) >= 0)
        {
            free_all(minishell);
            exit(minishell->status);
        }
		else
		{
			cmd = verify_path(temp_tree->argv[0], minishell->path);
			if (!cmd)
			{
				status = show_error(temp_tree->argv[0], ": Command not found", 127);
				free_all(minishell);
				exit(status);
			}
		}
		close(parent_tree->fd[STDOUT_FILENO]);
		close(parent_tree->fd[STDIN_FILENO]);
		execve(cmd, temp_tree->argv, minishell->envp);
        free_all(minishell);
		// execute_tree_commands(minishell);
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
	close(temp_tree->fd[STDOUT_FILENO]);
	close(temp_tree->fd[STDIN_FILENO]);
}

void	execute_tree_commands(t_minishell *minishell)
{
	t_command	*temp_tree;
	t_list		*temp_list;

	signal(SIGINT, &handle_signal_exec);
	temp_tree = minishell->tree_cmd;
	if (temp_tree->type == WORD)
	{
		if (temp_tree->redir)
			setup_redirs(temp_tree->redir);
		execute_single_command(minishell);
  }
	else
	{
		execute_pipe_command(minishell, temp_tree);
		temp_list = minishell->pid_list;
		while (temp_list)
		{
			ft_printf("pid: %d\n", (long)(temp_list->content));
			waitpid((pid_t)((long)(temp_list->content)), &minishell->status, 0);
			minishell->status = filter_status(minishell->status);
			temp_list = temp_list->next;
		}
		close_fds(minishell);
	}
	signal(SIGINT, &handle_signal);
}