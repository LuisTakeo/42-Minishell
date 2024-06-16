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

void	free_tree(t_command **tree)
{
	t_command	*temp;

	temp = *tree;
	if (temp->left)
		free_tree(&temp->left);
	if (temp->right)
		free_tree(&temp->right);
	if (temp->argv)
		free_arr(temp->argv);
	if (temp->redir)
		free_token(&(temp->redir));
	free(temp);
}

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

int	build_commands(t_minishell *minishell)
{
	int	status;

	get_token(minishell->input, &(minishell->tokens));
	if (!(minishell->tokens) || !(minishell->tokens->content)
		|| validate_tokens(minishell->tokens) == 1)
		return (EXIT_FAILURE);
	set_operator_type(&(minishell->tokens));
	status = verify_heredoc(minishell);
	if (status)
	{
		minishell->status = status;
		return (EXIT_FAILURE);
	}
	ft_generate_tree(minishell);
	return (EXIT_SUCCESS);
}

void	build_and_execute(t_minishell *minishell)
{
	add_history(minishell->input);
	if (build_commands(minishell))
	{
		free_resources_prompt(minishell);
		return ;
	}
	execute_tree_commands(minishell);
	free_resources_prompt(minishell);
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
		tcsetattr(STDIN_FILENO, TCSANOW, &term);
		control_status(0);
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

void	free_list(t_list **list)
{
	t_list	*temp;

	while (*list)
	{
		temp = *list;
		*list = (*list)->next;
		free(temp);
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
	free_arr(minishell.path);
	free_arr(minishell.envp);
	rl_clear_history();
	return (EXIT_SUCCESS);
}
