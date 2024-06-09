/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirects.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dde-fati <dde-fati@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/08 01:14:11 by dde-fati          #+#    #+#             */
/*   Updated: 2024/06/09 00:01:09 by dde-fati         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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
    char *line; 
    int pipefd[2]; 

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
        if (ft_strcmp(line, delim) == 0)
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

/*int    check_redirects(t_token *tokens, t_command *cmd)
{
	t_token   *temp;

	temp = tokens;
	while (temp)
	{
		if (temp->type == REDIR_IN)
		{
			if (set_infile(temp->content) == -1)
				return (EXIT_FAILURE);
		}
		else if (temp->type == REDIR_OUT || temp->type == APPEND)
		{
			if (set_outfile(temp->content) == -1)
				return (EXIT_FAILURE);
		}
		else if (temp->type == HEREDOC)
		{
			if (set_appendfile(temp->content) == -1)
				return (EXIT_FAILURE);
		}
		temp = temp->next;
	}
	return (EXIT_SUCCESS);
}*/
