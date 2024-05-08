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

t_command	*ft_newnodetree(char *name, char **args)
{
	t_command	*new_node;

	new_node = malloc(sizeof(t_list));
	if (!new_node)
		return (NULL);
	new_node->name = name;
	new_node->args = args;
	new_node->argc = 0;
	new_node->start = NULL;
	new_node->end = NULL;
	new_node->next = NULL;
	new_node->left = NULL;
	new_node->right = NULL;
	return (new_node);
}