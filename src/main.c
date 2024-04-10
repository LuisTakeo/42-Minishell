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

int	main(int argc, char **argv)
{
	if (argc > 1 || argv[1])
		return (0);
	prompt();
	return (0);
}
