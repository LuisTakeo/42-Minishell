/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dde-fati <dde-fati@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/02 03:14:53 by dde-fati          #+#    #+#             */
/*   Updated: 2024/06/02 03:46:52 by dde-fati         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static char	**dup_arr(char **arr)
{
	char	**new_arr;
	int		i;

	i = 0;
	while (arr[i])
		i++;
	new_arr = (char **)ft_calloc(sizeof(char *), i + 1);
	if (!new_arr)
		return (NULL);
	i = 0;
	while (arr[i])
	{
		new_arr[i] = ft_strdup(arr[i]);
		i++;
	}
	new_arr[i] = NULL;
	return (new_arr);
}

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
	free_arr(minishell->pid_list);
	free(minishell->input);
	minishell->input = NULL;
	if (minishell->tokens)
		free_token(&(minishell->tokens));
	minishell->tokens = NULL;
	if (minishell->tree_cmd)
		free_tree_cmd(&(minishell->tree_cmd));
	minishell->tree_cmd = NULL;
}

static void	set_exit_code(char **argv)
{
	int	exit_code;
	
	if (!argv[1])
		exit_code = 0;
	else if (ft_is_number(argv[1]))
		exit_code = ft_atoi(argv[1]);
	else
	{
		ft_fdprintf("minishell: exit: %s: numeric argument required\n", STDERR_FILENO, argv[1]);
		exit_code = 255;
	}
	exit(exit_code);
}

int	exit(t_minishell *minishell)
{
	char	**argv;
	
	ft_fdprintf("exit\n", STDERR_FILENO);
	if (minishell->tree_cmd->argc > 1)
	{
		ft_fdprintf("minishell: exit: too many arguments\n", STDERR_FILENO);
		return (EXIT_FAILURE);
	}
	argv = dup_arr(minishell->tree_cmd->argv);
	free_all(minishell);
	set_exit_code(minishell->tree_cmd->argv);
	return (EXIT_SUCCESS);
}
