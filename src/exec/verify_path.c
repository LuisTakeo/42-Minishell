/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   verify_path.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpaim-yu <tpaim-yu@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 20:31:54 by tpaim-yu          #+#    #+#             */
/*   Updated: 2024/04/18 20:31:54 by tpaim-yu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*verify_path(char *bin, char **path)
{
	int		response;
	int		i;
	char	*full_path;

	response = 0;
	i = 0;
	while (path[i])
	{
		full_path = ft_strjoin(path[i], bin);
		ft_printf("Access, it %s exists? %d \n", full_path,
			access(full_path, F_OK));
		ft_printf("Access, it %s executable? %d \n", full_path,
			access(full_path, X_OK));
		if (access(full_path, F_OK) == 0 && access(full_path, X_OK) == 0)
			return (full_path);
		free(full_path);
		i++;
	}
	return (NULL);
}