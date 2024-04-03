#include <unistd.h>
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <stdlib.h>
#include "../src/includes/minishell.h"

int main(void)
{
	char *test[] = {"cat", NULL, NULL};
	char *flags[] = {"-e", NULL};
	char *read;

	// readline gera stillreachables da própria readline
	// flag para readline -lreadline
	read = readline("> ");
	test[1] = read;
	// execve pega o caminho do binario como primeiro argumento
	// e um array de strings como comando e argumentos desse comando
	printf("%d ", execve("/usr/bin/cat", test, flags));
	free(read);
	return (0);
}