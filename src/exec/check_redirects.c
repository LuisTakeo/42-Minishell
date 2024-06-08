/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_redirects.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dde-fati <dde-fati@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/08 01:14:11 by dde-fati          #+#    #+#             */
/*   Updated: 2024/06/08 01:48:26 by dde-fati         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int    check_redirects(t_token *tokens, t_command *cmd)
{
    t_token   *temp;

    temp = tokens;
    while (temp)
    {
        if (temp->type == REDIR_IN)
        {
            if (set_infile(temp->content) == -1)
                return (EXIT_FAILURE);
        }
        else if (temp->type == REDIR_OUT || temp->type == APPEND)
        {
            if (set_outfile(temp->content) == -1)
                return (EXIT_FAILURE);
        }
        else if (temp->type == HEREDOC)
        {
            if (set_appendfile(temp->content) == -1)
                return (EXIT_FAILURE);
        }
        temp = temp->next;
    }
    return (EXIT_SUCCESS);
}
