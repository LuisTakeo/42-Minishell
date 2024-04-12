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

void	prompt(void)
{
	char	*input;
	t_token	*tokens;

	input = readline("minishell$ ");
	if (input)
	{
		add_history(input);
		printf("Input: %s\n\n", input);
		get_token(input, &tokens);
		free(input);
		free_token(&tokens);
	}
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
	int			i;
	extern char	**environ; // <---- puxa variáveis de ambiente

	path = get_paths(environ);
	prompt();
	i = 0;
	while (path[i])
		printf("%s\n", path[i++]);
	free_split(path);
	rl_clear_history();
	return (0);
}
