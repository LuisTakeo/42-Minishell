/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpaim-yu <tpaim-yu@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/26 18:59:01 by dde-fati          #+#    #+#             */
/*   Updated: 2024/06/06 21:51:47 by tpaim-yu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static char	*get_env_value(char *envp, int len)
{
	envp += len;
	if (*envp == '=')
		envp++;
	return (ft_strdup(envp));
}

char	*expand_env(char *var, char **envp)
{
	char	**temp;
	int		len;

	temp = envp;
	len = ft_strlen(var);
	while (*temp)
	{
		if (!ft_strncmp(var, (char *)(*temp), len))
			return (get_env_value(*temp, len));
		temp++;
	}
	return (NULL);
}

char	*expand_path(char **word, t_minishell *minishell)
{
	int		i;
	char	*temp;
	char	*new_word;

	(*word)++;
	if (!**word || (!ft_isalnum(**word) && **word != '_'))
		return (ft_strdup("$"));
	if (ft_isdigit(**word))
	{
		(*word)++;
		return (ft_strdup(""));
	}
	i = 0;
	temp = *word;
	while (**word && (ft_isalnum(**word) || **word == '_'))
	{
		(*word)++;
		i++;
	}
	temp = ft_substr(temp, 0, i);
	new_word = expand_env(temp, minishell->envp);
	free(temp);
	return (new_word);
}
