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

static void	sort_arr(char **arr)
{
	int	i;
	int	j;

	i = 0;
	j = 1;
	while (arr[i] && arr[j])
	{
		ft_fdprintf("%s\n", STDOUT_FILENO, arr[j]);
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
	int		i;

	envcp = get_env(env);

	return (EXIT_SUCCESS);
}

int	export(char *variable, char *env)
{
	if (!variable)
		return (print_env(env));

	return (EXIT_SUCCESS);
}