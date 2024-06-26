/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpaim-yu <tpaim-yu@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 20:19:53 by tpaim-yu          #+#    #+#             */
/*   Updated: 2024/04/25 20:19:53 by tpaim-yu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	print_env(char **envp)
{
	char	**temp;

	temp = envp;
	while (*temp != NULL)
	{
		if (ft_strchr(*temp, '='))
			ft_printf("%s\n", *temp);
		temp++;
	}
	return (0);
}
