#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#define FD_SIZE 2

int main(int argc, char const *argv[])
{
	int fd;
	int backup[FD_SIZE];

	backup[STDIN_FILENO] = dup(STDIN_FILENO);
	backup[STDOUT_FILENO] = dup(STDOUT_FILENO);
	fd = open("file", O_RDWR);
	dup2(fd, STDIN_FILENO);
	close(fd);
	write(STDOUT_FILENO, "hello world\n", 12);
	dup2(backup[STDOUT_FILENO], STDOUT_FILENO);
	write(STDOUT_FILENO, "minishell\n", 10);
	return 0;
}