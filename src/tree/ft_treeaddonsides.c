/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_treeaddonleft.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpaim-yu <tpaim-yu@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 18:28:28 by tpaim-yu          #+#    #+#             */
/*   Updated: 2024/05/21 18:28:28 by tpaim-yu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_treeaddonleft(t_command **treenode, t_command *treenew)
{
	t_command	*treetemp;

	if (!treenode || !treenew)
		return ;
	if (!*treenode)
		*treenode = treenew;
	treetemp = *treenode;
	ft_printf("treetemp->argv[0] -> %s\n", treetemp->argv[0]);
	while (treetemp && treetemp->left)
	{
		ft_printf("LOOP?\n");
		treetemp = treetemp->left;
	}
	ft_printf("tree_temp->argv[0] -> %s\n", treetemp->argv[0]);
	treetemp->left = treenew;
	treenew->parent = treetemp;
}

void	ft_treeaddonright(t_command **treenode, t_command *treenew)
{
	t_command	*treetemp;

	if (!treenode || !treenew)
		return ;
	if (!*treenode)
		*treenode = treenew;
	treetemp = *treenode;
	while (treetemp->right)
		treetemp = treetemp->right;
	treetemp->right = treenew;
	treenew->parent = treetemp;
}
