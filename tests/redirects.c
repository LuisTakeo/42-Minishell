/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirects.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dde-fati <dde-fati@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/08 01:14:11 by dde-fati          #+#    #+#             */
/*   Updated: 2024/06/10 20:10:08 by dde-fati         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <readline/readline.h>
#include <readline/history.h>

void	redirect_output(const char *filename)
{
	int	fd;
	
	fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd < 0)
	{
		perror("open");
		exit(EXIT_FAILURE);
	}
	if (dup2(fd, STDOUT_FILENO) < 0)
	{
		perror("dup2");
		exit(EXIT_FAILURE);
	}
	close(fd);
}

void	redirect_input(const char *filename)
{
	int	fd;
	
	fd = open(filename, O_RDONLY);
	if (fd < 0)
	{
		perror("open");
		exit(EXIT_FAILURE);
	}
	if (dup2(fd, STDIN_FILENO) < 0)
	{
		perror("dup2");
		exit(EXIT_FAILURE);
	}
	close(fd);
}

void	append_output(const char *filename)
{
	int	fd;
	
	fd = open(filename, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd < 0)
	{
		perror("open");
		exit(EXIT_FAILURE);
	}
	if (dup2(fd, STDOUT_FILENO) < 0)
	{
		perror("dup2");
		exit(EXIT_FAILURE);
	}
	close(fd);
}

void	heredoc(const char *delim)
{
	char	*line; 
	int		pipefd[2]; 

	line = NULL;
	if (pipe(pipefd) == -1)
	{
		perror("pipe");
		exit(EXIT_FAILURE);
	}
	while (1)
	{
		line = readline("> ");
		if (line == NULL)
			break;
		if (strcmp(line, delim) == 0)
		{
			free(line);
			break;
		}
		// Escreve a linha lida no pipe e adiciona uma nova linha ao final
		write(pipefd[1], line, strlen(line));
		write(pipefd[1], "\n", 1);
		free(line);
	}
	close(pipefd[1]);  // Fecha o descritor de escrita do pipe
	// Redireciona stdin (descritor de arquivo 0) para o descritor de leitura do pipe
	if (dup2(pipefd[0], STDIN_FILENO) < 0)
	{
		perror("dup2");
		exit(EXIT_FAILURE);
	}
	close(pipefd[0]);
}

void	execute_command(char **args)
{
	execvp(args[0], args);
	perror("execvp");
	exit(EXIT_FAILURE);
}

void	parse_and_execute(char *cmd)
{
	char *args[100];
	int arg_count = 0;
	char *token = strtok(cmd, " ");
	char *input_file = NULL;
	char *output_file = NULL;
	char *append_file = NULL;
	char *heredoc_delim = NULL;

	printf("token: %s\n", token);
	while (token != NULL) {
		if (strcmp(token, "<") == 0) {
			token = strtok(NULL, " ");
			if (token == NULL) {
				fprintf(stderr, "Syntax error: expected file after '<'\n");
				exit(EXIT_FAILURE);
			}
			input_file = token;
		} else if (strcmp(token, ">") == 0) {
			token = strtok(NULL, " ");
			if (token == NULL) {
				fprintf(stderr, "Syntax error: expected file after '>'\n");
				exit(EXIT_FAILURE);
			}
			output_file = token;
		} else if (strcmp(token, ">>") == 0) {
			token = strtok(NULL, " ");
			if (token == NULL) {
				fprintf(stderr, "Syntax error: expected file after '>>'\n");
				exit(EXIT_FAILURE);
			}
			append_file = token;
		} else if (strcmp(token, "<<") == 0) {
			token = strtok(NULL, " ");
			if (token == NULL) {
				fprintf(stderr, "Syntax error: expected delimiter after '<<'\n");
				exit(EXIT_FAILURE);
			}
			heredoc_delim = token;
		} else {
			args[arg_count++] = token;
		}
		token = strtok(NULL, " ");
	}
	args[arg_count] = NULL;

	if (input_file != NULL) {
		redirect_input(input_file);
	}
	if (output_file != NULL) {
		redirect_output(output_file);
	}
	if (append_file != NULL) {
		append_output(append_file);
	}
	if (heredoc_delim != NULL) {
		heredoc(heredoc_delim);
	}
	execute_command(args);
}

int	main(int argc, char *argv[])
{
	if (argc != 2)
	{
		fprintf(stderr, "Usage: %s \"command\"\n", argv[0]);
		exit(EXIT_FAILURE);
	}
	parse_and_execute(argv[1]);
	return 0;
}
