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

	signal(SIGINT, &handle_signal);
	signal(SIGQUIT, SIG_IGN);
	tokens = NULL;
	input = readline("minishell$ ");
	while (input)
	{
		add_history(input);
		get_token(input, &tokens);
		if (tokens)
			exec_command(ft_split(tokens->content, ' '), 0, environ, path);
		if (input)
			free(input);
		if (tokens)
			free_token(&tokens);
		input = readline("minishell$ ");
	}
	ft_printf("Exit\n");
}

void	free_split(char **split)
{
	int	i;

	i = 0;
	while (split[i])
	{
		free(split[i]);
		i++;
	}
	free(split);
}

int	main(void)
{
	char		**path;
	extern char	**environ; // <---- puxa variáveis de ambiente
	char		**envp;

	path = get_paths(environ);
	envp = get_env(environ);
	prompt(envp, path);
	free_split(path);
	rl_clear_history();
	return (EXIT_SUCCESS);
}
