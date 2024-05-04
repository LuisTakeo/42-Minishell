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

char	*validate_var_name(char *var)
{
	int	i;

	i = 1;
	if (var[0] && !(ft_isalpha(var[0]) || var[0] == '_'))
		return (var);
	while (var[i] && var[i] != '=')
	{
		if (!(ft_isalnum(var[i]) || var[i] == '_'))
			return (var);
		i++;
	}
	return (NULL);
}

int	export(char *variable, char ***env)
{
	char	**new_envp;
	char	*var;
	int		size;
	int		i;

	if (!variable || !*variable)
		return (print_order_env((*env)));
	var = validate_var_name(variable);
	if (var)
		return (ft_fdprintf("'%s': not a valid identifier\n",
				STDERR_FILENO, var));
	size = 0;
	while ((*env)[size])
		size++;
	new_envp = calloc(sizeof(char *), size + 2);
	i = -1;
	while ((*env)[++i])
		new_envp[i] = ft_strdup((*env)[i]);
	new_envp[i] = ft_strdup(variable);
	new_envp[size + 1] = NULL;
	if (*env)
		free_arr(*env);
	*env = new_envp;
	return (EXIT_SUCCESS);
}
