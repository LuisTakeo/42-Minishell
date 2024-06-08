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
	{
		*treenode = treenew;
		return ;
	}
	treetemp = *treenode;
	while (treetemp && treetemp->left)
		treetemp = treetemp->left;
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
