/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpaim-yu <tpaim-yu@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 17:08:18 by tpaim-yu          #+#    #+#             */
/*   Updated: 2024/05/02 17:08:18 by tpaim-yu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	swap_arr(char **wordA, char **wordB)
{
	char	*temp;

	temp = *wordA;
	*wordA = *wordB;
	*wordB = temp;
}

static void	sort_arr(char **arr)
{
	int	i;
	int	j;

	i = 0;
	j = 1;
	while (arr[i] && arr[j])
	{
		if (ft_strncmp(arr[i], arr[j], ft_strlen(arr[i])) > 0)
			swap_arr(&arr[i], &arr[j]);
		j++;
		if (!arr[j] && arr[i + 1])
		{
			i++;
			j = i + 1;
		}
	}
}

int	print_env(char **env)
{
	char	**envcp;
	char	**key_value;
	int		i;
	int		j;

	envcp = get_env(env);
	sort_arr(envcp);
	i = 0;
	while (envcp[i])
	{
		key_value = ft_split(envcp[i], '=');
		j = 1;
		ft_printf("declare -x %s=\"", key_value[0]);
		while (key_value[j])
			ft_printf("%s", key_value[j++]);
		ft_printf("\"\n");
		free_arr(key_value);
		i++;
	}
	free_arr(envcp);
	return (EXIT_SUCCESS);
}

int	export(char *variable, char **env)
{
	if (!variable)
		return (print_env(env));

	return (EXIT_SUCCESS);
}