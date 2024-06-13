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

void	execute_command(t_minishell *minishell, t_command *temp_tree,
	int is_left)
{
	pid_t	pid;

	(void)temp_tree;
	(void)is_left;
	pid = fork();
	if (pid == -1)
	{
		minishell->status = show_error("fork: ", strerror(errno), 1);
		return ;
	}
	if (!pid)
	{
		// if (parent_tree->parent->type == PIPE)
		// 	dup2(parent_tree->fd[STDIN_FILENO], STDIN_FILENO);
		// dup2(parent_tree->fd[STDOUT_FILENO], STDOUT_FILENO);
		// close(temp_tree->parent->fd[STDOUT_FILENO]);
		// close(temp_tree->parent->fd[STDIN_FILENO]);
        if (is_builtin(temp_tree->argv, minishell) >= 0)
        {
            free_all(minishell);
            exit(minishell->status);
        }
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
			minishell->status = (minishell->status >> 8) & 0xff;
			temp_list = temp_list->next;
		}
	}
	signal(SIGINT, &handle_signal);
}