/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpaim-yu <tpaim-yu@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/04 19:48:04 by tpaim-yu          #+#    #+#             */
/*   Updated: 2024/05/04 19:48:04 by tpaim-yu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	echo(char **args)
{
	int	i;
	int	is_break_line;

	if (!args)
		return (EXIT_FAILURE);
	i = 0;
	is_break_line = 1;
	if (args[i] && !ft_strncmp(args[i], "-n", 3))
	{
		is_break_line = 0;
		i++;
	}
	while (args[i])
	{
		ft_fdprintf("%s", STDOUT_FILENO, args[i]);
		if (args[i + 1])
			ft_fdprintf(" ", STDOUT_FILENO);
		i++;
	}
	if (is_break_line)
		ft_fdprintf("\n", STDOUT_FILENO);
	return (EXIT_SUCCESS);
}