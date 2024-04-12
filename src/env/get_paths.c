/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_paths.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpaim-yu <tpaim-yu@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 21:06:46 by tpaim-yu          #+#    #+#             */
/*   Updated: 2024/04/11 21:06:46 by tpaim-yu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	**insert_paths(char *paths)
{
	char	**split;
	char	*temp;
	int		i;

	split = ft_split(paths, ':');
	i = 0;
	while (split[i])
	{
		temp = split[i];
		split[i] = ft_strjoin(split[i], "/");
		free(temp);
		i++;
	}
	return (split);
}

char	**get_paths(char **env)
{
	char	**temp;

	temp = env;
	while (*temp)
	{
		if (!ft_strncmp("PATH=", (char *)(*temp), 5))
			return (insert_paths((char *)(*temp) + 5));
		temp++;
	}
	return (NULL);
}
