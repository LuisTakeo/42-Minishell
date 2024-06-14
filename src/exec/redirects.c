/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirects.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dde-fati <dde-fati@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/08 01:14:11 by dde-fati          #+#    #+#             */
/*   Updated: 2024/06/12 01:54:40 by dde-fati         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	reset_fds(t_minishell *minishell)
{
	if ((dup2(minishell->stdin_backup, STDIN_FILENO) < 0)
		|| (dup2(minishell->stdout_backup, STDOUT_FILENO) < 0))
	{
		perror("dup2");
		return ;
	}
}

int	redirect_input(const char *filename, t_token *redir)
{
	int	fd;
	
	fd = open(filename, O_RDONLY);
	if (fd < 0)
	{
		perror("open");
		return(EXIT_FAILURE);
	}
	if (dup2(fd, STDIN_FILENO) < 0)
	{
		perror("dup2");
		return(EXIT_FAILURE);
	}
	redir->file_fd = fd;
	close(fd);
	return (EXIT_SUCCESS);
}

int	redirect_output(const char *filename, t_token *redir)
{
	int	fd;
	
	fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd < 0)
	{
		perror("open");
		return(EXIT_FAILURE);
	}
	if (dup2(fd, STDOUT_FILENO) < 0)
	{
		perror("dup2");
		return(EXIT_FAILURE);
	}
	redir->file_fd = fd;
	close(fd);
	return (EXIT_SUCCESS);
}

int	append_output(const char *filename, t_token *redir)
{
	int	fd;
	
	fd = open(filename, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd < 0)
	{
		perror("open");
		return(EXIT_FAILURE);
	}
	if (dup2(fd, STDOUT_FILENO) < 0)
	{
		perror("dup2");
		return(EXIT_FAILURE);
	}
	redir->file_fd = fd;
	close(fd);
	return (EXIT_SUCCESS);
}
// adaptar com arquivo temporário
// incluir validação do signal
// restaurar valor padrão da variável estática e do comportamento padrão do signal
int	heredoc(const char *delim, t_token *redir)
{
    char *line; 
    int pipefd[2]; 

    line = NULL;
    if (pipe(pipefd) == -1)
	{
        perror("pipe");
        return(EXIT_FAILURE);
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
        write(pipefd[1], line, ft_strlen(line));
        write(pipefd[1], "\n", 1);
        free(line);
    }
    close(pipefd[1]);  // Fecha o descritor de escrita do pipe
    // Redireciona stdin (descritor de arquivo 0) para o descritor de leitura do pipe
    if (dup2(pipefd[0], STDIN_FILENO) < 0)
	{
        perror("dup2");
        return(EXIT_FAILURE);
    }
	redir->file_fd = pipefd[0]; // validar descritor
    close(pipefd[0]);
	return (EXIT_SUCCESS);
}

t_token	*add_redirection(t_token *redirs)
{
	t_token	*new_redir;

	init_token(&new_redir);
	if (!new_redir)
		return (NULL);
	new_redir->content = ft_strdup(redirs->next->content);
	new_redir->type = redirs->type;
	new_redir->file_fd = -1;
	new_redir->next = NULL;
	new_redir->prev = NULL;
	return (new_redir);
}

t_token	*ft_generate_redirs(t_token *token)
{
	t_token	*redirs;
	t_token	*current;

	redirs = NULL;
	current = token;
	while (current && current->type != PIPE)
	{
		if (current->type == REDIR_IN || current->type == REDIR_OUT
			|| current->type == APPEND || current->type == HEREDOC)
			redirs = add_redirection(current);
		current = current->next;
	}
	return (redirs);
}

// talvez não seja necessário um loop, apenas os ifs
int    setup_redirs(t_token *redir)
{
	while (redir)
	{
		if (redir->type == REDIR_IN)
		{
			if (redirect_input(redir->content, redir) == 1)
				return (EXIT_FAILURE);
		}
		else if (redir->type == REDIR_OUT)
		{
			if (redirect_output(redir->content, redir) == 1)
				return (EXIT_FAILURE);
		}
		else if (redir->type == APPEND)
		{
			if (append_output(redir->content, redir) == 1)
				return (EXIT_FAILURE);
		}
		else if (redir->type == HEREDOC)
		{
			if (heredoc(redir->content, redir) == 1)
				return (EXIT_FAILURE);
		}
		redir = redir->next;
	}
	return (EXIT_SUCCESS);
}
