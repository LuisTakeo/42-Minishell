#include <unistd.h>
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <stdlib.h>
#include "../src/includes/minishell.h"

#include <sys/wait.h>

int main(void)
{
	char *test[] = {"ls", NULL, NULL};
	char *flags[] = {NULL};
	char *read;
	__pid_t pid;

	// readline gera stillreachables da própria readline
	// flag para readline -lreadline
	read = NULL;
	pid = fork();
	if (!pid)
		fork();

	printf("%d aaa\n", pid);
	if (pid)
	{
		printf("Esperando processo filho...\n");
		wait(0);
		printf("Continuando...\n");
	}
	printf("1 2 3\n1 2 3\n");
	// execve pega o caminho do binario como primeiro argumento
	// e um array de strings como comando e argumentos desse comando
	if (!pid)
		printf("Printf: %d \n", execve("/usr/bin/ls", test, flags));
	printf("Chegou aqui\nPID: %d\n", pid);
	free(read);
	return (0);
}