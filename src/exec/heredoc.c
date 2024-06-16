/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dde-fati <dde-fati@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/16 14:50:51 by dde-fati          #+#    #+#             */
/*   Updated: 2024/06/16 14:52:53 by dde-fati         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	handle_sig_heredoc(int signal)
{
	if (signal == SIGINT)
	{
		ft_putstr_fd("\n", STDOUT_FILENO);
		close(STDIN_FILENO);
		control_status(130);
	}
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
