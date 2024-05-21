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


void	prompt(t_minishell *minishell)
{
	char	**test_command;

	prepare_signals();
	minishell->tokens = NULL;
	test_command = NULL;
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
		get_token(minishell->input, &(minishell->tokens));
		test_command = ft_split(minishell->tokens->content, ' ');
		if (minishell->tokens)
		{
			if (is_builtin(test_command, minishell->envp) >= 0)
				ft_printf("Builtin\n");
			else
				exec_command(test_command, 0, minishell);
		}
		if (minishell->input)
			free(minishell->input);
		if (minishell->tokens)
			free_token(&(minishell->tokens));
		minishell->tokens = NULL;
		if (test_command)
			free_arr(test_command);
		test_command = NULL;
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
	extern char	**environ;
	char		*test;
	char		**env;
	char		**comando = ft_split("ls -la", ' ');
	t_list		*temp;


	test = NULL;
	env = get_env(__environ);
	pipe(fd);
	printf("Descritores de arquivo: in = %d, out = %d\n", fd[0], fd[1]);
	pid = fork();
	if (pid)
	{
		ft_lstadd_back(&minishell->pid_list, ft_lstnew((void *)((long)pid)));
		ft_printf("%d %d ", (long *)(minishell->pid_list->content), pid);
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
		ft_lstadd_back(&minishell->pid_list, ft_lstnew((void *)((long)pid)));
		ft_printf("%d %d ", (long *)(minishell->pid_list->content), pid);
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
		ft_lstadd_back(&minishell->pid_list, ft_lstnew((void *)((long)pid)));
		ft_printf("%d %d ", (long *)(minishell->pid_list->content), pid);
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
	temp = minishell->pid_list;
	// lógica para implantar waits de cada processo
	// wait são aplicados no final, após fds fechados para evitar problemas
	while (temp)
	{
		waitpid((pid_t)((long)(temp->content)), &status, 0);
		temp = temp->next;
	}
	ft_lstclear(&minishell->pid_list, free);
}

int	main(void)
{
	t_minishell	minishell;
	extern char	**environ;

	minishell.envp = get_env(environ);
	minishell.path = get_paths(minishell.envp);
	minishell.input = NULL;
	minishell.pid_list = NULL;
	test(&minishell);
	// pwd();
	// change_dir(ft_strdup("./src"));
	// pwd();
	prompt(&minishell);
	ft_printf("Exit\n");
	free_arr(minishell.path);
	free_arr(minishell.envp);
	rl_clear_history();
	return (EXIT_SUCCESS);
}
