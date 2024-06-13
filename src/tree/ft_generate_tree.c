/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_generate_tree.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpaim-yu <tpaim-yu@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 18:41:38 by tpaim-yu          #+#    #+#             */
/*   Updated: 2024/05/21 18:41:38 by tpaim-yu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_token	*find_last_pipe(t_token *token)
{
	t_token	*temp;
	t_token	*last_pipe;

	temp = token;
	last_pipe = token;
	while (temp)
	{
		if (temp->type == PIPE)
			last_pipe = temp;
		temp = temp->next;
	}
	return (last_pipe);
}

t_token	*find_previous_pipe(t_token *token, t_minishell *minishell)
{
	t_token	*temp;
	t_token	*previous_pipe;

	if (!token)
		return (NULL);
	temp = token;
	previous_pipe = minishell->tokens;
	while (temp)
	{
		if (temp->type == PIPE)
			return (temp);
		temp = temp->prev;
	}
	return (previous_pipe);
}

t_command	*ft_gen_command_node(t_token *token, t_minishell *minishell)
{
	t_command	*new_node;

	new_node = ft_newtreenode(NULL);
	if (!new_node)
		return (NULL);
	new_node->argv = ft_generate_argv(token, minishell);
	new_node->redir = ft_generate_redirs(token);
	new_node->type = WORD;
	new_node->left = NULL;
	new_node->right = NULL;
	return (new_node);
}

t_command	*ft_gen_pipe_node(t_token *token, t_minishell *minishell)
{
	t_command	*new_node;

	new_node = ft_newtreenode(NULL);
	if (!new_node)
		return (NULL);
	new_node->argv = ft_split("|", ' ');
	new_node->type = PIPE;
	new_node->left = NULL;
	new_node->right = ft_gen_command_node(token->next, minishell);
	return (new_node);
}

void	ft_generate_tree(t_minishell *minishell)
{
	t_token		*temp;

	temp = find_last_pipe(minishell->tokens);
	while (temp)
	{
		if (temp->type == PIPE)
			ft_treeaddonleft(&minishell->tree_cmd,
				ft_gen_pipe_node(temp, minishell));
		else
		{
			ft_treeaddonleft(&minishell->tree_cmd,
				ft_gen_command_node(temp, minishell));
			break ;
		}
		temp = find_previous_pipe(temp->prev, minishell);
	}
}
