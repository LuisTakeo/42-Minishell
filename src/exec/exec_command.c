/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_command.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpaim-yu <tpaim-yu@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 17:57:33 by tpaim-yu          #+#    #+#             */
/*   Updated: 2024/04/16 17:57:33 by tpaim-yu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	show_error(char *content, char *error, int num_error)
{
	ft_putstr_fd(content, STDERR_FILENO);
	ft_putendl_fd(error, STDERR_FILENO);
	return (num_error);
}

int	is_valid_command(char **full_path, char *path, t_minishell *minishell)
{
	DIR		*dir;

	dir = opendir(path);
	*full_path = verify_path(path, minishell->path);
	if ((*full_path && access(*full_path, X_OK) != 0) || dir)
	{
		closedir(dir);
		return (show_error(path, ": BUH! Not an executable", 126));
	}
	if (!*full_path)
		return (show_error(path, ": BUH! Command not found", 127));
	return (0);
}

// alterar o id conforme redirects
int	exec_command(char **arrstr, int id, t_minishell *minishell)
{
	int		i_status;
	char	*full_path;

	i_status = 0;
	full_path = NULL;
	i_status = is_valid_command(&full_path, arrstr[0], minishell);
	if (i_status)
	{
		if (full_path)
			free(full_path);
		return (i_status);
	}
	id = fork();
	if (!id)
	{
		execve(full_path, arrstr, minishell->envp);
		free(full_path);
		free_all(minishell);
		exit(EXIT_FAILURE);
	}
	waitpid(id, &i_status, 0);
	i_status = filter_status(i_status);
	if (full_path && ft_strncmp(full_path, arrstr[0],
			ft_strlen(full_path) + 1))
		free(full_path);
	reset_fds(minishell);
	return (i_status);
}
