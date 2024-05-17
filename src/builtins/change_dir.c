/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   change_dir.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpaim-yu <tpaim-yu@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 14:57:31 by dde-fati          #+#    #+#             */
/*   Updated: 2024/05/15 14:35:38 by tpaim-yu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	is_actual_dir(const char *path)
{
	return (*path == '\0' || !ft_strncmp(path, ".", ft_strlen(".") + 1)
		|| !ft_strncmp(path, "\".\"", ft_strlen("\".\"") + 1));
}

static char	*generate_full_path(const char *home, const char *path)
{
	char	*full_path;

	full_path = ft_strjoin(home, (path + 1));
	return (full_path);
}

static int	print_error_cd(char **path)
{
	ft_fdprintf("cd: ", STDERR_FILENO);
	perror(NULL);
	ft_fdprintf("cd: %s %s\n", STDERR_FILENO, (*path), strerror(errno));
	free((*path));
	return (EXIT_FAILURE);
}
// nota -> passar conteúdo com aspas para change_dir
//		-> comportamento diferente de cd ~ para cd "~"
//	upt	-> não é necessário tratar o ~
int	change_dir(char *path)
{
	char	*full_path;
	char	*home;

	if (path && is_actual_dir(path))
		return (EXIT_SUCCESS);
	full_path = NULL;
	home = getenv("HOME");
	if (path == NULL || !ft_strncmp(path, "~", ft_strlen("~") + 1))
		path = home;
	else if (!ft_strncmp(path, "~/", 2))
	{
		full_path = generate_full_path(home, path);
		path = full_path;
	}
	if (chdir(path) == -1)
		return (print_error_cd(&path));
	free(full_path);
	return (EXIT_SUCCESS);
}

// verificar se for NULL ir para home
// fazer verificação com access
// fazer verificação de ~
// https://www.unix.com/man-page/v7/1/cd/
// https://ss64.com/bash/cd.html
// https://stackoverflow.com/questions/41147818/no-man-page-for-the-cd-command
