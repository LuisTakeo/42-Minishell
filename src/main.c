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
		add_history(input);
		get_token(input, &tokens);
		if (input[0])
			test_command = ft_split(tokens->content, ' '); // test
		if (tokens)
			exec_command(test_command, 0, environ, path);
		if (input)
			free(input);
		if (tokens)
			free_token(&tokens);
		tokens = NULL;
		if (test_command) // test
			free_arr(test_command);
		test_command = NULL;
	}
	ft_printf("Exit\n");
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
	// char		*test[] = {"-n","Teste", "teste2", NULL};

	envp = NULL;
	path = get_paths(environ);
	envp = get_env(environ);
	// export("123", &envp); //export tests
	// export("_123", &envp);
	// export("-123", &envp);
	// export("_abc123", &envp);
	// export("_abcBCD=123", &envp);
	// export(NULL, &envp);
	// ft_printf("\n\n");
	// export("_abcBCD=456", &envp);
	// export("_ddd=123", &envp);
	// export("123", &envp);
	// export(NULL, &envp);
	// echo(test);
	echo(NULL);
	prompt(envp, path);
	free_arr(path);
	free_arr(envp);
	rl_clear_history();
	return (EXIT_SUCCESS);
}
