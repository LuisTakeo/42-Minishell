/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   frees.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpaim-yu <tpaim-yu@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/16 14:25:19 by tpaim-yu          #+#    #+#             */
/*   Updated: 2024/06/16 14:25:19 by tpaim-yu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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

void	free_child(t_minishell *minishell)
{
	free_all(minishell);
	exit(minishell->status);
}
