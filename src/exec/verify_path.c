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
	int		i;
	char	*full_path;

	if (!*bin)
		return (NULL);
	if (access(bin, F_OK) == 0)
		return (ft_strdup(bin));
	if (!path)
		return (NULL);
	i = 0;
	while (path[i])
	{
		full_path = ft_strjoin(path[i], bin);
		if (access(full_path, F_OK) == 0)
			return (full_path);
		free(full_path);
		i++;
	}
	return (NULL);
}
