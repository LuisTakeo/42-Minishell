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

char	**get_env(char **envp)
{
	char	**env;
	int		env_size;
	int		i;

	env_size = 0;
	ft_printf("passou aqui\n %s!", envp[0]);
	while (envp[env_size])
		env_size++;
	env = malloc(sizeof(char *) * env_size + 1);
	env[env_size] = NULL;
	i = 0;
	while (envp[i])
	{
		env[i] = envp[i];
		i++;
	}
	return (env);
}
