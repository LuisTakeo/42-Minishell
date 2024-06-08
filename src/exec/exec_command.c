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

int	exec_command(char **arrstr, int id, t_minishell *minishell)
{
	int		i;
	char	*full_path;

	i = 0;
	full_path = verify_path(arrstr[0], minishell->path);
	if (!full_path)
		return (show_error(arrstr[0], ": Command not found", 127));
	id = fork();
	if (!id)
	{
		execve(full_path, arrstr, minishell->envp);
		exit(EXIT_FAILURE);
	}
	waitpid(id, &i, 0);
	minishell->status = i;
	// ft_printf("Response: %d\n", minishell->status);
	if (full_path && ft_strncmp(full_path, arrstr[0],
			ft_strlen(full_path) + 1))
		free(full_path);
	return (0);
}
