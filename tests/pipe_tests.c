#include "../src/includes/minishell.h"

int	main(void)
{
	int			fd[2];
	int			pid;
	extern char	**environ;
	char		*env;
	char		**comando = ft_split("ls -la", ' ');

	env = get_env(__environ);
	pipe(fd);
	printf("Descritores de arquivo: leitura = %d, escrita = %d\n", fd[0], fd[1]);
	pid = fork();
	if (!pid)
	{
		dup2(fd[STDOUT_FILENO], STDOUT_FILENO);
		close(fd[STDOUT_FILENO]);
		close(fd[STDIN_FILENO]);
		execve("/usr/bin/ls", comando, env);
		exit(EXIT_FAILURE);
	}
	free_arr(comando);
	comando = ft_split("grep p", ' ');
	pid = fork();
	if (!pid)
	{
		dup2(fd[STDIN_FILENO], STDIN_FILENO);
		close(fd[STDOUT_FILENO]);
		close(fd[STDIN_FILENO]);
		execve("/usr/bin/grep", comando, env);
		exit(EXIT_FAILURE);
	}
	close(fd[0]);
	close(fd[1]);
	printf("Descritores de arquivo: leitura = %d, escrita = %d\n", fd[0], fd[1]);
	pipe(fd);
	printf("Descritores de arquivo: leitura = %d, escrita = %d\n", fd[0], fd[1]);
	return (EXIT_SUCCESS);
}
