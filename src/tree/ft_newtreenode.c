/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_newnodetree.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpaim-yu <tpaim-yu@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/04 22:03:26 by tpaim-yu          #+#    #+#             */
/*   Updated: 2024/05/04 22:03:26 by tpaim-yu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_command	*ft_newtreenode(char **args)
{
	t_command	*new_node;

	new_node = malloc(sizeof(t_command));
	if (!new_node)
		return (NULL);
	new_node->argv = args;
	new_node->argc = 0;
	new_node->left = NULL;
	new_node->right = NULL;
	new_node->redir = NULL;
	new_node->argc = 0;
	new_node->type = -1;
	new_node->left = NULL;
	new_node->right = NULL;
	new_node->parent = NULL;
	return (new_node);
}
