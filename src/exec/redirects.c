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

int	redirect_input(char *filename)
{
	int	fd;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
	{
		perror("open");
		return (EXIT_FAILURE);
	}
	if (dup2(fd, STDIN_FILENO) < 0)
	{
		perror("dup2");
		return (EXIT_FAILURE);
	}
	close(fd);
	return (EXIT_SUCCESS);
}

int	redirect_output(char *filename)
{
	int	fd;

	fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd < 0)
	{
		perror("open");
		return (EXIT_FAILURE);
	}
	if (dup2(fd, STDOUT_FILENO) < 0)
	{
		perror("dup2");
		return (EXIT_FAILURE);
	}
	close(fd);
	return (EXIT_SUCCESS);
}

int	append_output(char *filename)
{
	int	fd;

	fd = open(filename, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd < 0)
	{
		perror("open");
		return (EXIT_FAILURE);
	}
	if (dup2(fd, STDOUT_FILENO) < 0)
	{
		perror("dup2");
		return (EXIT_FAILURE);
	}
	close(fd);
	return (EXIT_SUCCESS);
}

// adaptar com arquivo temporário
// incluir validação do signal
// restaurar valor padrão da variável estática e do comportamento padrão do signal
int	heredoc(char *delim)
{
	char	*line;
	int		fd;

	fd = open(delim, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd < 0)
	{
		perror("open");
		return (EXIT_FAILURE);
	}
	line = NULL;
	while (1)
	{
		line = readline("> ");
		if (line == NULL)
			break ;
		if (ft_strcmp(line, delim) == 0)
		{
			free(line);
			break ;
		}
		write(fd, line, ft_strlen(line));
		write(fd, "\n", 1);
		free(line);
	}
	close(fd);
	return (EXIT_SUCCESS);
}

void	add_redirection(t_token **redirs, t_token *new_redir)
{
	t_token	*temp;

	init_token(&temp);
	if (!temp)
		return ;
	temp->content = ft_strdup(new_redir->next->content);
	temp->type = new_redir->type;
	ft_tokenadd_back(redirs, temp);
}

t_token	*ft_generate_redirs(t_token **token)
{
	t_token	*redirs;
	t_token	*current;
	t_token	*next;

	init_token(&redirs);
	if (!redirs)
		return (NULL);
	current = *token;
	while (current && current->type != PIPE)
	{
		next = current->next;
		if (current->type == REDIR_IN || current->type == REDIR_OUT
			|| current->type == APPEND || current->type == HEREDOC)
		{
			add_redirection(&redirs, current);
			ft_tokendelone(token, current);
			ft_tokendelone(token, current->next);
		}
		current = next;
	}
	return (redirs);
}

int	setup_redirs(t_token *redir)
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
