/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   change_dir.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpaim-yu <tpaim-yu@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 14:57:31 by dde-fati          #+#    #+#             */
/*   Updated: 2024/05/31 16:35:25 by tpaim-yu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	is_actual_dir(const char *path)
{
	return (*path == '\0' || !ft_strncmp(path, ".", ft_strlen(".") + 1));
}

static int	print_error_cd(char **path, char *error_msg)
{
	if (error_msg)
		ft_fdprintf("cd: %s\n", STDERR_FILENO, error_msg);
	else
	{
		ft_fdprintf("cd: ", STDERR_FILENO);
		perror(NULL);
		ft_fdprintf("cd: %s %s\n", STDERR_FILENO, (*path), strerror(errno));
	}
	return (EXIT_FAILURE);
}

void	set_pwd(t_minishell *minishell)
{
	char	*new_pwd;
	char	*old_pwd;
	char	*temp;
	int		i;

	i = -1;
	while (minishell->envp[++i])
		if (!ft_strncmp(minishell->envp[i], "PWD", 3))
			break ;
	old_pwd = ft_strjoin("OLD", minishell->envp[i]);
	temp = getcwd(NULL, 0);
	new_pwd = ft_strjoin("PWD=", temp);
	export(new_pwd, &minishell->envp);
	export(old_pwd, &minishell->envp);
	free(old_pwd);
	free(new_pwd);
	free(temp);
}

int	verify_and_change_dir(char *path, t_minishell *minishell)
{
	char	*full_path;
	char	*home;

	full_path = NULL;
	home = getenv("HOME");
	if (path == NULL || !ft_strncmp(path, "~", ft_strlen("~") + 1))
		path = home;
	else if (!ft_strncmp(path, "~/", 2))
	{
		full_path = ft_strjoin(home, path);
		path = full_path;
	}
	if (chdir(path) == -1)
		return (EXIT_FAILURE);
	else
		set_pwd(minishell);
	if (full_path)
		free(full_path);
	return (EXIT_SUCCESS);
}

int	change_dir(char **path, t_minishell *minishell)
{
	if (path[1] && path[2])
		return (print_error_cd(path, "too many arguments"));
	if (path[1] && is_actual_dir(path[1]))
		return (EXIT_SUCCESS);
	return (verify_and_change_dir(path[1], minishell));
}
