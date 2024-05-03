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

static void	show_error(char *content, char *error)
{
	ft_putstr_fd(content, 2);
	ft_putstr_fd(error, 2);
}

void	exec_command(char **arrstr, int id, char **env, char **path)
{
	int		i;
	char	*full_path;

	i = 0;
	full_path = verify_path(arrstr[0], path);
	if (!full_path)
	{
		show_error(arrstr[0], ": Command not found\n");
		return ;
	}
	id = fork();
	if (id)
	{
		waitpid(id, &i, 0);
		ft_printf("Response: %d\n", i);
	}
	if (!id)
	{
		ft_printf("Processo filho: %d\n", id);
		execve(full_path, arrstr, env);
	}
	if (full_path && ft_strncmp(full_path, arrstr[0],
			ft_strlen(full_path) + 1))
		free(full_path);
}
