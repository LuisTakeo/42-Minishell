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

char	*join_word(char *word, char *new_word)
{
	char	*temp;

	if (!word)
		return (new_word);
	temp = ft_strjoin(word, new_word);
	if (word)
		free(word);
	if (new_word)
		free(new_word);
	return (temp);
}

char	*expand_vars_and_quotes(char *word, t_minishell *minishell)
{
	char	*full_word;
	char	*temp_word;
	char	*temp;

	full_word = NULL;
	temp_word = NULL;
	temp = word;
	while (*temp)
	{
		if (*temp == '\'')
			temp_word = expand_simple_quotes(&temp);
		else if (*temp == '"')
			temp_word = expand_double_quotes(&temp, minishell);
		else if (*temp == '$')
			temp_word = expand_path(&temp, minishell);
		else
			temp_word = expand_word(&temp);
		// temp_free = full_word;
		// ft_printf("FULL WORD -> %s\n", temp_word);
		full_word = join_word(full_word, temp_word);
		temp_word = NULL;
	}
	// ft_printf("FULL WORD %s\n", full_word);
	// quando encontrar variavel, chamar função de expandir var
	// quando encontrar "" chamar função de expandir ""
	return (full_word);
}

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
			previous_pipe = temp;
		temp = temp->prev;
	}
	ft_printf("previous pipe %s\n", previous_pipe->content);
	return (previous_pipe);
}

t_command	*ft_gen_command_node(t_token *token, t_minishell *minishell)
{
	t_command	*new_node;

	new_node = ft_newtreenode(NULL);
	if (!new_node)
		return NULL;
	new_node->argv = ft_generate_argv(token, minishell);
	new_node->type = WORD;
	new_node->left = NULL;
	new_node->right = NULL;
	ft_printf("gerou command node\n");
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
	ft_printf("gerou pipe node\n");
	return (new_node);
}

void	ft_generate_tree(t_minishell *minishell)
{
	t_token		*temp;

	temp = find_last_pipe(minishell->tokens);
	ft_printf("last pipe %s\n", temp->content);
	while (temp)
	{
		if (temp->type == PIPE)
			ft_treeaddonleft(&minishell->tree_cmd,
				ft_gen_pipe_node(temp, minishell));
		else
		{
			ft_printf("entrou agui\n");
			ft_treeaddonleft(&minishell->tree_cmd,
				ft_gen_command_node(temp, minishell));
			break;
		}
		temp = find_previous_pipe(temp->prev, minishell);
	}

}
