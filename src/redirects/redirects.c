/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirects.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dde-fati <dde-fati@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/08 01:14:11 by dde-fati          #+#    #+#             */
/*   Updated: 2024/06/09 23:44:43 by dde-fati         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	redirect_input(const char *filename)
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
	close(fd);
	return (EXIT_SUCCESS);
}

int	redirect_output(const char *filename)
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
	close(fd);
	return (EXIT_SUCCESS);
}

int	append_output(const char *filename)
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
	close(fd);
	return (EXIT_SUCCESS);
}

int	heredoc(const char *delim)
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
    close(pipefd[0]);
	return (EXIT_SUCCESS);
}

int	add_redirection(t_token *redirs, t_minishell *minishell)
{
	t_token	*node;

	init_token(&node);
	if (!node)
		return (EXIT_FAILURE);
	node->content = ft_strdup(redirs->next->content);
	node->type = redirs->type;
	ft_tokenadd_back(&minishell->tree_cmd->redir, node);
	return (EXIT_SUCCESS);
}

void	get_redirs(t_minishell **minishell)
{
	t_token	*temp;

	temp = (*minishell)->tokens;
	while (temp)
	{
		if (temp->type != PIPE && temp->type != WORD)
			add_redirection(temp, *minishell);
		else
			temp = temp->next;
	}
}

int    setup_redirs(t_token *redir)
{
	while (redir)
	{
		if (redir->type == REDIR_IN)
		{
			if (redirect_input(redir->content) == 1)
				return (EXIT_FAILURE);
		}
		else if (redir->type == REDIR_OUT)
		{
			if (redirect_output(redir->content) == 1)
				return (EXIT_FAILURE);
		}
		else if (redir->type == APPEND)
		{
			if (append_output(redir->content) == 1)
				return (EXIT_FAILURE);
		}
		else if (redir->type == HEREDOC)
		{
			if (heredoc(redir->content) == 1)
				return (EXIT_FAILURE);
		}
		redir = redir->next;
	}
	return (EXIT_SUCCESS);
}
