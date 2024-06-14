#include "../src/includes/minishell.h"

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