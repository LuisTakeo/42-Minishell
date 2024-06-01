/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dde-fati <dde-fati@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/26 18:59:01 by dde-fati          #+#    #+#             */
/*   Updated: 2024/05/26 19:31:45 by dde-fati         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static char	*get_env_value(char *envp, int len)
{
	envp += len;
	if (*envp == '=')
		envp++;
	return (ft_strdup(envp));
}

char	*expand_env(char *var, char **envp)
{
	char	**temp;
	int		len;

	temp = envp;
	len = ft_strlen(var);
	while (*temp)
	{
		if (!ft_strncmp(var, (char *)(*temp), len))
			return (get_env_value(*temp, len));
		temp++;
	}
	return (NULL);
}
