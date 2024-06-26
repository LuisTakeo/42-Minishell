/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dde-fati <dde-fati@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/02 03:14:53 by dde-fati          #+#    #+#             */
/*   Updated: 2024/06/08 17:40:27 by dde-fati         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	ft_is_number(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

void	free_all(t_minishell *minishell)
{
	free_arr(minishell->path);
	free_arr(minishell->envp);
	if (minishell->pid_list)
		free_list(&minishell->pid_list);
	if (minishell->input)
		free(minishell->input);
	if (minishell->tokens)
		free_token(&minishell->tokens);
	if (minishell->tree_cmd)
		free_tree(&minishell->tree_cmd);
	close(STDIN_FILENO);
	close(STDOUT_FILENO);
	close(STDERR_FILENO);
	close(minishell->stdin_backup);
	close(minishell->stdout_backup);
	rl_clear_history();
}

static void	set_exit_code(char **args, t_minishell **minishell)
{
	int	exit_code;
	int	number;

	exit_code = 0;
	if (!args[1])
	{
		if ((*minishell)->status)
			exit_code = (*minishell)->status;
	}
	else if (ft_is_number(args[1]))
	{
		number = ft_atoi(args[1]);
		if (number < 0 || number > 255)
			exit_code = number % 256;
		else
			exit_code = number;
	}
	else
	{
		ft_fdprintf("minishell: exit: %s: numeric argument required\n",
			STDERR_FILENO, args[1]);
		exit_code = 2;
	}
	free_all(*minishell);
	exit(exit_code);
}

int	exit_builtin(char **args, t_minishell *minishell)
{
	ft_fdprintf("exit\n", STDERR_FILENO);
	if (args[1] && args[2])
	{
		if (ft_is_number(args[1]))
		{
			ft_fdprintf("minishell: exit: too many arguments\n", STDERR_FILENO);
			return (EXIT_FAILURE);
		}
		else
			set_exit_code(args, &minishell);
	}
	set_exit_code(args, &minishell);
	return (EXIT_SUCCESS);
}
