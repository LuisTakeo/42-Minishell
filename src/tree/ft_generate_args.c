/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_generate_args.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpaim-yu <tpaim-yu@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 14:36:36 by tpaim-yu          #+#    #+#             */
/*   Updated: 2024/05/31 14:36:36 by tpaim-yu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	count_args(t_token *tokens)
{
	t_token	*temp;
	int		i;

	i = 0;
	temp = tokens;
	while (temp && temp->type != PIPE)
	{
		if (temp->type == WORD)
			i++;
		else
			temp = temp->next;
		temp = temp->next;
	}
	return (i);
}

char	**ft_generate_argv(t_token *tokens, t_minishell *minishell)
{
	int		i;
	t_token	*temp;
	char	**argv;

	i = count_args(tokens);
	temp = tokens;
	if (!i)
		return (NULL);
	argv = (char **)ft_calloc(i + 1, sizeof(char *));
	temp = tokens;
	i = -1;
	while (temp && temp->type != PIPE)
	{
		if (temp->type == WORD)
			argv[++i] = expand_vars_and_quotes(temp->content, minishell);
		else
			temp = temp->next;
		temp = temp->next;
	}
	return (argv);
}
