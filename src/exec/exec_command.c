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

void	exec_command(char **arrstr, int id, char **env, char **path)
{
	int 	i;
	char	*full_path;

	i = 0;
	full_path = ft_strjoin(path[6], arrstr[0]);
	ft_printf("%s\n", full_path);

	id = fork();
	if (id)
	{
		waitpid(id, &i, 0);
		ft_printf("Response: %d\n", i);
		free(full_path);
	}
	if (!id)
	{

		ft_printf("Processo filho: %d\n", id);
		// execve("/usr/bin/bash", arrstr, env);
		execve(full_path, arrstr, env);
		// execve("/usr/bin/clear", arrstr, env);
	}
}
