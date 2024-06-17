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

void	free_resources_prompt(t_minishell *minishell)
{
	if (minishell->input)
		free(minishell->input);
	if (minishell->tokens)
		free_token(&(minishell->tokens));
	if (minishell->tree_cmd)
		free_tree(&(minishell->tree_cmd));
	if (minishell->pid_list)
		free_list(&(minishell->pid_list));
	minishell->input = NULL;
	minishell->tokens = NULL;
	minishell->tree_cmd = NULL;
	minishell->pid_list = NULL;
}

void	prompt(t_minishell *minishell)
{
	static struct termios	term;

	tcgetattr(STDIN_FILENO, &term);
	prepare_signals();
	minishell->tokens = NULL;
	while (1)
	{
		reset_fds(minishell);
		minishell->input = readline("minishell$ ");
		if (control_status(-1))
			minishell->status = control_status(-1);
		control_status(0);
		if (!minishell->input)
			break ;
		if (minishell->input[0])
			build_and_execute(minishell);
		free_resources_prompt(minishell);
		tcsetattr(STDIN_FILENO, TCSANOW, &term);
		control_status(0);
	}
}

int	main(void)
{
	t_minishell	minishell;
	extern char	**environ;

	if (environ)
		minishell.envp = get_env(environ);
	minishell.path = get_paths(minishell.envp);
	minishell.input = NULL;
	minishell.pid_list = NULL;
	minishell.tree_cmd = NULL;
	minishell.status = 0;
	minishell.stdin_backup = dup(STDIN_FILENO);
	minishell.stdout_backup = dup(STDOUT_FILENO);
	prompt(&minishell);
	ft_printf("Exit\n");
	free_all(&minishell);
	return (EXIT_SUCCESS);
}
