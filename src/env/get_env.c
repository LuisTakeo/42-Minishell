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
	while (envp[env_size])
		env_size++;
	env = ft_calloc(sizeof(char *), env_size + 1);
	env[env_size] = NULL;
	i = 0;
	while (envp[i])
	{
		env[i] = ft_strdup(envp[i]);
		i++;
	}
	return (env);
}

char	*get_single_env(char *env_name, char **envp)
{
	int		i;
	int		env_len;
	char	*temp;

	i = -1;
	env_len = ft_strlen(env_name);
	while (envp[++i])
		if (!ft_strncmp(env_name, envp[i], env_len)
			&& (envp[i][env_len] == '=' || !envp[i][env_len]))
			break ;
	temp = envp[i];
	if (temp)
	{
		while (*temp && *temp != '=')
			temp++;
		if (!(*temp))
			return (NULL);
		temp++;
		temp = ft_strdup(temp);
		ft_printf("%s\n", temp);
	}
	return (temp);
}
