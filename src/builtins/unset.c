/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpaim-yu <tpaim-yu@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/28 17:58:22 by dde-fati          #+#    #+#             */
/*   Updated: 2024/06/08 21:09:51 by tpaim-yu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	is_key_in_envp(const char *key, t_minishell *minishell)
{
	int	i;

	i = 0;
	while (minishell->envp[i])
	{
		if (ft_strncmp(minishell->envp[i], key, ft_strlen(key)) == 0)
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

static int	unset_env(const char *key, t_minishell *minishell)
{
	int		i;
	int		j;
	char	**new_env;
	char	*new_key;

	i = -1;
	j = -1;
	new_key = get_single_env((char *)key, minishell->envp);
	new_env = (char **)malloc(sizeof(char *) * (
				get_envp_len(minishell->envp, new_key) + 1));
	while (minishell->envp[++i])
		if (ft_strncmp(minishell->envp[i], new_key, ft_strlen(new_key)) != 0)
			new_env[++j] = ft_strdup(minishell->envp[i]);
	new_env[++j] = NULL;
	free_arr(minishell->envp);
	minishell->envp = new_env;
	free(new_key);
	return (EXIT_SUCCESS);
}

int	unset(const char **key, t_minishell *minishell)
{
	int		status_error;
	char	**temp;

	status_error = 0;
	if (!key || key[1] == NULL)
		return (status_error);
	temp = (char **)key;
	(temp)++;
	while (*temp)
	{
		if (is_key_in_envp(*temp, minishell) == 1)
		{
			if (validate_var_name(*temp))
				status_error = show_error(*temp, ": not an identifier", 1);
		}
		else
			unset_env(*temp, minishell);
		(temp)++;
	}
	free_arr(minishell->path);
	minishell->path = get_paths(minishell->envp);
	return (status_error);
}
