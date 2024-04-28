/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dde-fati <dde-fati@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 20:06:13 by dde-fati          #+#    #+#             */
/*   Updated: 2024/04/28 17:59:49 by dde-fati         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	pwd(void)
{
	char	*pwd;

	pwd = getcwd(NULL, 0);
	ft_fdprintf("%s\n", STDOUT_FILENO, pwd);
	free(pwd);
}
