/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpaim-yu <tpaim-yu@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 18:14:40 by tpaim-yu          #+#    #+#             */
/*   Updated: 2024/03/28 18:14:40 by tpaim-yu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/minishell.h"

void	handle_signal(int signum)
{
	if (signum == SIGINT)
	{
		ft_putstr_fd("\n", STDOUT_FILENO);
		rl_on_new_line();
		rl_replace_line("", STDIN_FILENO);
		rl_redisplay();
	}
}

void	prepare_signals(void)
{
	signal(SIGINT, &handle_signal);
	signal(SIGQUIT, SIG_IGN);
}

void	free_tree(t_command **tree)
{
	t_command	*temp;

	temp = *tree;
	if (temp->left)
		free_tree(&temp->left);
	if (temp->right)
		free_tree(&temp->right);
	if (temp->argv)
		free_arr(temp->argv);
	free(temp);
}

void	free_resources_prompt(t_minishell *minishell)
{
	if (minishell->input)
		free(minishell->input);
	if (minishell->tokens)
		free_token(&(minishell->tokens));
	if (minishell->tree_cmd)
		free_tree(&(minishell->tree_cmd));
	if (minishell->pid_list)
		ft_lstclear(&(minishell->pid_list), free);
	minishell->input = NULL;
	minishell->tokens = NULL;
	minishell->tree_cmd = NULL;
	minishell->pid_list = NULL;
}

void	execute_single_command(t_minishell *minishell)
{
	t_command	*temp_cmd;

	temp_cmd = minishell->tree_cmd;
	// necessário adaptar execução dos builtins em caso de redirs
	// leaks na execução de bultins com redirects
	// echo entrando em loop infinito com >
	if (is_builtin(temp_cmd->argv, minishell) >= 0) 
		return ;
	if (temp_cmd->redir)
		minishell->status = exec_command(temp_cmd->argv, temp_cmd->redir->file_fd, minishell);
	else
		minishell->status = exec_command(temp_cmd->argv, 0, minishell);
	minishell->status = (minishell->status >> 8) & 0xff;
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
		// close(parent_tree->fd[STDOUT_FILENO]);
		// close(parent_tree->fd[STDIN_FILENO]);
		// execute_tree_commands(minishell);
		exit(EXIT_FAILURE);
	}
	ft_lstadd_back(&(minishell->pid_list), ft_lstnew((void *)((long)pid)));
}

void	execute_pipe_command(t_minishell *minishell, t_command *temp_tree)
{
	// pipe(temp_tree->fd);
	(void)temp_tree;
	if (temp_tree->left && temp_tree->left->type == PIPE)
		execute_pipe_command(minishell, temp_tree->left);
	if (temp_tree->left && temp_tree->left->type != PIPE)
		execute_command(minishell, temp_tree->left, 1);
	if (temp_tree->right && temp_tree->right->type != PIPE)
		execute_command(minishell, temp_tree->right, 0);
	// close(temp_tree->fd[STDOUT_FILENO]);
	// close(temp_tree->fd[STDIN_FILENO]);
}

void	execute_tree_commands(t_minishell *minishell)
{
	t_command	*temp_tree;
	t_list		*temp_list;

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
}

int	build_commands(t_minishell *minishell)
{
	get_token(minishell->input, &(minishell->tokens));
	if (!(minishell->tokens) || !(minishell->tokens->content)
		|| validate_tokens(minishell->tokens) == 1)
		return (EXIT_FAILURE);
	set_operator_type(&(minishell->tokens));
	ft_generate_tree(minishell);
	print_tokens(minishell->tree_cmd->redir);
	return (EXIT_SUCCESS);
}

void	prompt(t_minishell *minishell)
{
	prepare_signals();
	minishell->tokens = NULL;
	while (1)
	{
		minishell->input = readline("minishell$ ");
		if (!minishell->input)
			break ;
		if (!minishell->input[0])
		{
			free(minishell->input);
			continue ;
		}
		add_history(minishell->input);
		if (build_commands(minishell))
		{
			free_resources_prompt(minishell);
			continue ;
		}
		execute_tree_commands(minishell);
		free_resources_prompt(minishell);
	}
}

void	free_arr(char **arr)
{
	int	i;

	if (!arr || !arr[0])
		return ;
	i = 0;
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}

void	test(t_minishell *minishell)
{
	int			fd[2];
	int			fd2[2];
	int			status;
	pid_t			pid;
	// int			pid2;
	// int			pid3;
	// extern char	**environ;
	// char		*test;
	char		**env;
	char		**comando = ft_split("ls -la", ' ');
	t_list		*temp;


	// test = NULL;
	env = get_env(__environ);
	pipe(fd);
	printf("Descritores de arquivo: in = %d, out = %d\n", fd[0], fd[1]);
	pid = fork();
	if (pid)
	{
		ft_lstadd_back(&minishell->pid_list, ft_lstnew((void *)((long)pid)));
		ft_printf("%d %d ", (long *)(minishell->pid_list->content), pid);
		// ft_lstadd_back(&minishell->pid_list, ft_lstnew(ft_itoa(pid)));
		// ft_printf("%s %d ", (ft_lstlast(minishell->pid_list))->content, pid);
	}
	if (!pid)
	{
		dup2(STDIN_FILENO, STDIN_FILENO);
		dup2(fd[STDOUT_FILENO], STDOUT_FILENO);
		// duplicando a saida do pipe para saida padrão
		close(fd[STDOUT_FILENO]);
		close(fd[STDIN_FILENO]);
		execve("/usr/bin/ls", comando, env);
		exit(EXIT_FAILURE);
	}
	free_arr(comando);
	// wait(NULL);
	comando = ft_split("wc -l", ' ');
	pipe(fd2);
	printf("Descritores de arquivo: in = %d, out = %d\n", fd2[0], fd2[1]);
	pid = fork();
	if (pid)
	{
		ft_lstadd_back(&(minishell->pid_list), ft_lstnew((void *)((long)pid)));
		ft_printf("%d %d ", (long *)(minishell->pid_list->content), pid);
		// ft_lstadd_back(&minishell->pid_list, ft_lstnew(ft_itoa(pid)));
		// ft_printf("%s %d ", (ft_lstlast(minishell->pid_list))->content, pid);
	}
	if (!pid)
	{
		dup2(fd[STDIN_FILENO], STDIN_FILENO);
		// duplicando a entrada do pipe para entrada padrão
		dup2(fd2[STDOUT_FILENO], STDOUT_FILENO);
		// duplicando a saida do próximo pipe para a saida padrão
		// ft_printf("Entrou aqui");
		close(fd[STDOUT_FILENO]);
		close(fd[STDIN_FILENO]);
		close(fd2[STDOUT_FILENO]);
		close(fd2[STDIN_FILENO]);
		execve("/usr/bin/wc", comando, env);
		exit(EXIT_FAILURE);
	}
	close(fd[STDOUT_FILENO]);
	close(fd[STDIN_FILENO]);
	// wait(NULL);
	// dup2(fd[STDIN_FILENO], fd2[STDOUT_FILENO]);
	// ft_printf("%d", 123);
	// close(fd[STDIN_FILENO]);
	free_arr(comando);
	comando = ft_split("grep 1", ' ');
	pid = fork();
	if (pid)
	{
		ft_lstadd_back(&(minishell->pid_list), ft_lstnew((void *)((long)pid)));
		ft_printf("%d %d ", (long *)(minishell->pid_list->content), pid);
		// ft_lstadd_back(&minishell->pid_list, ft_lstnew(ft_itoa(pid)));
		// ft_printf("%s %d ", (ft_lstlast(minishell->pid_list))->content, pid);
	}
	if (!pid)
	{
		dup2(fd2[STDIN_FILENO], STDIN_FILENO);
		close(fd2[STDOUT_FILENO]);
		close(fd2[STDIN_FILENO]);
		execve("/usr/bin/grep", comando, env);
		exit(EXIT_FAILURE);
	}
	close(fd2[0]);
	close(fd2[1]);
	free_arr(comando);
	temp = minishell->pid_list;
	// lógica para implantar waits de cada processo
	// wait são aplicados no final, após fds fechados para evitar problemas
	while (temp)
	{
		waitpid((pid_t)((long)(temp->content)), &status, 0);
		temp = temp->next;
	}
	free_arr(env);
	temp = minishell->pid_list;
	ft_lstclear(&temp, free);
}

int	main(void)
{
	t_minishell	minishell;
	extern char	**environ;

	if (environ)
		minishell.envp = get_env(environ);
	minishell.path = get_paths(minishell.envp);
	minishell.input = NULL;
	minishell.pid_list = NULL;
	minishell.tree_cmd = NULL;
	minishell.status = 0;
	minishell.stdin_backup = dup(STDIN_FILENO);
	minishell.stdout_backup = dup(STDOUT_FILENO);
	prompt(&minishell);
	ft_printf("Exit\n");
	free_arr(minishell.path);
	free_arr(minishell.envp);
	rl_clear_history();
	return (EXIT_SUCCESS);
}
