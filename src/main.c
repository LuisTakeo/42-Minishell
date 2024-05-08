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

void	prompt(char **environ, char **path)
{
	char	*input;
	t_token	*tokens;
	char	**test_command; // test

	signal(SIGINT, &handle_signal);
	signal(SIGQUIT, SIG_IGN);
	tokens = NULL;
	test_command = NULL;
	while ((input = readline("minishell$ ")))
	{
		if (!input[0])
		{
			free(input);
			continue ;
		}
		add_history(input);
		get_token(input, &tokens);
		test_command = ft_split(tokens->content, ' '); // test
		if (tokens)
		{
			if (is_builtin(test_command, environ) >= 0)
				ft_printf("Builtin\n");
			else
				exec_command(test_command, 0, environ, path);
		}
		if (input)
			free(input);
		if (tokens)
			free_token(&tokens);
		tokens = NULL;
		if (test_command) // test
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
	char		**path;
	extern char	**environ;
	char		**envp;

	envp = NULL;
	path = get_paths(environ);
	envp = get_env(environ);
	echo(NULL);
	prompt(envp, path);
	ft_printf("Exit\n");
	free_arr(path);
	free_arr(envp);
	rl_clear_history();
	return (EXIT_SUCCESS);
}
