/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_builtin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpaim-yu <tpaim-yu@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 19:48:20 by tpaim-yu          #+#    #+#             */
/*   Updated: 2024/05/08 19:48:20 by tpaim-yu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	is_builtin(char **command, char **env)
{
	if (!env)
		return (0);
	if (!ft_strncmp(command[0], "cd", ft_strlen("cd") + 1))
		return (change_dir("."));
	if (!ft_strncmp(command[0], "echo", ft_strlen("echo") + 1))
		return (echo(command));
	if (!ft_strncmp(command[0], "exit", ft_strlen("exit") + 1))
		return (ft_fdprintf("Exit\n", STDOUT_FILENO));
	if (!ft_strncmp(command[0], "env", ft_strlen("env") + 1))
		return (print_env(env));
	if (!ft_strncmp(command[0], "export", ft_strlen("export") + 1))
		return (export(NULL, &env));
	if (!ft_strncmp(command[0], "unset", ft_strlen("unset") + 1))
		return (unset(NULL, env));
	if (!ft_strncmp(command[0], "pwd", ft_strlen("pwd") + 1))
		return (pwd());
	return (-1);
}