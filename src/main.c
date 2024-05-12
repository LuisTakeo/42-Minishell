/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpaim-yu <tpaim-yu@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 18:14:40 by tpaim-yu          #+#    #+#             */
/*   Updated: 2024/03/28 18:14:40 by tpaim-yu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/minishell.h"

void	handle_signal(int signum)
{
	if (signum == SIGINT)
	{
		ft_putstr_fd("\n", STDOUT_FILENO);
		rl_on_new_line();
		rl_replace_line("", STDIN_FILENO);
		rl_redisplay();
	}
}

void	prepare_signals(void)
{
	signal(SIGINT, &handle_signal);
	signal(SIGQUIT, SIG_IGN);
}

void	prompt(t_minishell *minishell)
{
	char	**test_command;

	prepare_signals();
	minishell->tokens = NULL;
	test_command = NULL;
	while (1)
	{
		minishell->input = readline("minishell$ ");
		if (!minishell->input)
			break ;
		if (!minishell->input[0])
		{
			free(minishell->input);
			continue ;
		}
		add_history(minishell->input);
		get_token(minishell->input, &(minishell->tokens));
		test_command = ft_split(minishell->tokens->content, ' ');
		if (minishell->tokens)
		{
			if (is_builtin(test_command, minishell->envp) >= 0)
				ft_printf("Builtin\n");
			else
				exec_command(test_command, 0, minishell);
		}
		if (minishell->input)
			free(minishell->input);
		if (minishell->tokens)
			free_token(&(minishell->tokens));
		minishell->tokens = NULL;
		if (test_command)
			free_arr(test_command);
		test_command = NULL;
	}
}


void	free_arr(char **arr)
{
	int	i;

	if (!arr || !arr[0])
		return ;
	i = 0;
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}

int	main(void)
{
	t_minishell	minishell;
	extern char	**environ;

	minishell.envp = get_env(environ);
	minishell.path = get_paths(minishell.envp);
	minishell.input = NULL;
	prompt(&minishell);
	ft_printf("Exit\n");
	free_arr(minishell.path);
	free_arr(minishell.envp);
	rl_clear_history();
	return (EXIT_SUCCESS);
}
