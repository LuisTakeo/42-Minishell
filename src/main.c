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

void	prompt(char **environ, char **path)
{
	char	*input;
	t_token	*tokens;

	tokens = NULL;
	input = readline("minishell$ ");
	while (input)
	{
		add_history(input);
		ft_printf("Input: %s\n\n", input);
		get_token(input, &tokens);
		if (tokens)
			exec_command(ft_split(tokens->content, ' '), 0, environ, path);
		// exec_command(ft_split("bash", ' '), 0, environ);
		if (input)
			free(input);
		if (tokens)
			free_token(&tokens);
		input = readline("minishell$ ");
	}
	ft_printf("\n");
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

	path = get_paths(environ);
	prompt(environ, path);
	free_split(path);
	rl_clear_history();
	return (0);
}
