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

void	env(char **envp)
{
	char	**temp;

	temp = envp;
	while (*temp != NULL)
	{
		ft_printf("%s\n", *temp);
		temp++;
	}
}
