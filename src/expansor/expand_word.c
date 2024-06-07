/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_word.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpaim-yu <tpaim-yu@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 21:40:06 by tpaim-yu          #+#    #+#             */
/*   Updated: 2024/06/06 21:40:06 by tpaim-yu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*expand_word(char **word)
{
	char	*temp;
	int		i;

	temp = *word;
	i = 0;
	while (temp[i] && !ft_strchr(QUOTES, temp[i]) && temp[i] != '$')
		i++;
	*word += i;
	return (ft_substr(temp, 0, i));
}