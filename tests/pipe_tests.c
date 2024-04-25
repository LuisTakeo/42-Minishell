#include "../src/includes/minishell.h"

int	main(void)
{
	int	fd[2];

	pipe(fd);
	printf("Descritores de arquivo: leitura = %d, escrita = %d\n", fd[0], fd[1]);
	close(fd[0]);
	close(fd[1]);
	printf("Descritores de arquivo: leitura = %d, escrita = %d\n", fd[0], fd[1]);
	pipe(fd);
	printf("Descritores de arquivo: leitura = %d, escrita = %d\n", fd[0], fd[1]);
	return (EXIT_SUCCESS);
}