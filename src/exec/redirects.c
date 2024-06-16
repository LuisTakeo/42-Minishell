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
		perror("minishell");
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
		perror("minishell");
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
		perror("minishell");
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

int	verify_heredoc(t_minishell *minishell)
{
	t_token	*temp;
	int		i;
	int		status;

	i = 0;
	status = 0;
	temp = minishell->tokens;
	while (temp)
	{
		if (temp->type == HEREDOC)
			status = heredoc(&temp->next->content, i++);
		if (status)
			return (status);
		temp = temp->next;
	}
	return (status);
}

char	*generate_heredoc_name(int index)
{
	char	*full_name;
	char	*index_text;

	index_text = ft_itoa(index);
	full_name = ft_strjoin("/tmp/heredoc-", index_text);
	free(index_text);
	return (full_name);
}

void	handle_sig_heredoc(int signal)
{
	if (signal == SIGINT)
	{
		ft_putstr_fd("\n", STDOUT_FILENO);
		close(STDIN_FILENO);
		control_status(130);
	}
}

int	read_heredoc(char *delim, int fd)
{
	char	*line;

	line = NULL;
	signal(SIGINT, &handle_sig_heredoc);
	while (1)
	{
		line = readline("> ");
		if (line == NULL || control_status(-1))
		{
			if (!control_status(-1))
				ft_fdprintf("Warning: heredoc "
					"delimited by EOF. Wanted delim: %s\n", 2, delim);
			break ;
		}
		if (ft_strcmp(line, delim) == 0)
		{
			free(line);
			break ;
		}
		ft_putendl_fd(line, fd);
		free(line);
	}
	signal(SIGINT, &handle_signal);
	return (control_status(-1));
}

int	heredoc(char **str, int index)
{
	char	*full_name;
	int		fd;
	int		status;

	status = 0;
	full_name = generate_heredoc_name(index);
	fd = open(full_name, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd < 0)
	{
		perror("open");
		return (EXIT_FAILURE);
	}
	status = read_heredoc(*str, fd);
	close(fd);
	control_status(0);
	free(*str);
	*str = full_name;
	return (status);
}

void	add_redir(t_token **rds, t_token *new_rd, t_minishell *minishell)
{
	t_token	*temp;

	init_token(&temp);
	if (!temp)
		return ;
	(temp)->content = expand_vars_and_quotes(new_rd->next->content, minishell);
	(temp)->type = new_rd->type;
	ft_tokenadd_back(rds, temp);
}

t_token	*ft_generate_redirs(t_token **token, t_minishell *minishell)
{
	t_token	*redirs;
	t_token	*current;
	t_token	*next;

	redirs = NULL;
	current = *token;
	while (current && current->type != PIPE)
	{
		next = current->next;
		if (current->type == REDIR_IN || current->type == REDIR_OUT
			|| current->type == APPEND || current->type == HEREDOC)
		{
			add_redir(&redirs, current, minishell);
		}
		current = next;
	}
	return (redirs);
}

int	setup_redirs(t_token *redir)
{
	while (redir)
	{
		if (redir->type == REDIR_IN || redir->type == HEREDOC)
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
		redir = redir->next;
	}
	return (EXIT_SUCCESS);
}
