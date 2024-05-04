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

int	calculate_n_size(char *text, char delimiter)
{
	int	i;

	i = 0;
	while (text[i] && text[i] != delimiter)
		i++;
	return (i);
}

int	is_var_exists(char *var, char ***env)
{
	char	**temp;
	int		size_temp;
	int		size_var;
	int		i;

	temp = (*env);
	size_var = calculate_n_size(var, '=');
	i = 0;
	while (temp[i])
	{
		size_temp = calculate_n_size(temp[i], '=');
		if (size_temp == size_var && !ft_strncmp(temp[i], var, size_temp))
		{
			free(temp[i]);
			temp[i] = ft_strdup(var);
			return (1);
		}
		i++;
	}
	return (0);
}

void	insert_key_value(char *variable, char ***env)
{
	int		size;
	int		i;
	char	**new_envp;

	size = 0;
	if (is_var_exists(variable, env))
		return ;
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
}

int	export(char *variable, char ***env)
{
	char	*var;

	if (!variable || !*variable)
		return (print_order_env((*env)));
	var = validate_var_name(variable);
	if (var)
		return (ft_fdprintf("'%s': not a valid identifier\n",
				STDERR_FILENO, var));
	insert_key_value(variable, env);
	return (EXIT_SUCCESS);
}
