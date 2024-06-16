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
	if (error)
		ft_putendl_fd(error, STDERR_FILENO);
	else
		perror(NULL);
	return (num_error);
}

static int	verify_abs_path(char *path)
{
	if (access(path, F_OK) == 0 && access(path, X_OK) == 0)
		return (1);
	return (0);
}

int	is_valid_command(char **full_path, char *path, t_minishell *minishell)
{
	if (verify_abs_path(path))
	{
		*full_path = path;
		return (EXIT_SUCCESS);
	}
	*full_path = verify_path(path, minishell->path);
	if (!*full_path)
		return (show_error(path, ": BUH! Command not found", 127));
	return (0);
}

void	child_single(char *full_path, char **arrstr, t_minishell *minishell)
{
	execve(full_path, arrstr, minishell->envp);
	free(full_path);
	free_all(minishell);
	exit(EXIT_FAILURE);
}

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
		full_path = NULL;
		return (i_status);
	}
	id = fork();
	if (!id)
		child_single(full_path, arrstr, minishell);
	waitpid(id, &i_status, 0);
	i_status = filter_status(i_status);
	if (full_path && ft_strncmp(full_path, arrstr[0],
			ft_strlen(full_path) + 1))
		free(full_path);
	reset_fds(minishell);
	return (i_status);
}
