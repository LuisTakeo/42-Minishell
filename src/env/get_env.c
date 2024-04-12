/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpaim-yu <tpaim-yu@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 20:55:23 by tpaim-yu          #+#    #+#             */
/*   Updated: 2024/04/11 20:55:23 by tpaim-yu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_list	*get_env(char **envp)
{
	t_list	*env;
	char	**temp;

	env = NULL;
	temp = envp;
	while (*temp)
	{
		ft_lstadd_back(&env, ft_lstnew(*temp));
		temp++;
	}
	return (env);
}

