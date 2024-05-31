/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpaim-yu <tpaim-yu@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/28 17:58:22 by dde-fati          #+#    #+#             */
/*   Updated: 2024/05/31 14:45:02 by tpaim-yu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	is_key_in_envp(const char *key, char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], key, ft_strlen(key)) == 0)
			return (EXIT_SUCCESS);
		i++;
	}
	return (EXIT_FAILURE);
}

static int	get_envp_len(char **envp, const char *key)
{
	int	i;
	int	occ;

	i = 0;
	occ = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], key, ft_strlen(key)) != 0)
			occ++;
		i++;
	}
	return (occ);
}

static int	unset_env(const char *key, char **envp)
{
	int		i;
	int		j;
	char	**new_env;
	char	*new_key;

	i = 0;
	j = 0;
	new_key = ft_strjoin(key, "=");
	new_env = (char **)malloc(sizeof(char *) * (
				get_envp_len(envp, new_key) + 1));
	while (envp[i])
	{
		if (ft_strncmp(envp[i], new_key, ft_strlen(new_key)) != 0)
		{
			new_env[j] = ft_strdup(envp[i]);
			j++;
		}
		i++;
	}
	new_env[j] = NULL;
	free_arr(envp);
	envp = new_env;
	free(new_key);
	return (EXIT_SUCCESS);
}

int	unset(const char *key, char **envp)
{
	// int	status_error;

	if (key == NULL)
		return (EXIT_FAILURE);
	else if (is_key_in_envp(key, envp) == 1)
	{
		ft_fdprintf("unset: %s: not an identifier\n", STDERR_FILENO, key);
		return (EXIT_FAILURE);
	}
	unset_env(key, envp);
	return (EXIT_SUCCESS);
}
