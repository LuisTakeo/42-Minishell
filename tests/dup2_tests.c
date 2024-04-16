#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>

int main(int argc, char const *argv[])
{
	int fd;
	int backup;

	backup = dup(1);
	fd = open("file", O_RDWR);
	dup2(fd, 1);
	close(fd);
	write(1, "hello world\n", 12);
	dup2(backup, 1);
	write(1, "minishell\n", 10);
	return 0;
}