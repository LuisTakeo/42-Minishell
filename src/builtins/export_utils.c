/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpaim-yu <tpaim-yu@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 21:25:05 by tpaim-yu          #+#    #+#             */
/*   Updated: 2024/05/03 21:25:05 by tpaim-yu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	swap_arr(char **wordA, char **wordB)
{
	char	*temp;

	temp = *wordA;
	*wordA = *wordB;
	*wordB = temp;
}

void	sort_arr(char **arr)
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

static void	print_key_value(char *value)
{
	char	*cpy;

	cpy = value;
	while (*cpy && *cpy != '=')
	{
		ft_putchar_fd(*cpy, STDOUT_FILENO);
		cpy++;
	}
	if (*cpy)
	{
		ft_putchar_fd(*cpy, STDOUT_FILENO);
		cpy++;
	}
	if (*cpy)
		ft_fdprintf("\"%s\"", STDOUT_FILENO, cpy);
	else
		ft_fdprintf("\"\"", STDOUT_FILENO);
	ft_putchar_fd('\n', STDOUT_FILENO);
}

int	print_order_env(char **env)
{
	char	**envcp;
	int		i;

	envcp = get_env(env);
	sort_arr(envcp);
	i = 0;
	while (envcp[i])
	{
		ft_fdprintf("Declare -x ", STDOUT_FILENO);
		print_key_value(envcp[i]);
		i++;
	}
	free_arr(envcp);
	return (EXIT_SUCCESS);
}
