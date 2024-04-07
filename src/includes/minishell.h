/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpaim-yu <tpaim-yu@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 18:14:16 by tpaim-yu          #+#    #+#             */
/*   Updated: 2024/03/28 18:14:16 by tpaim-yu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <limits.h>
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>

# include "../../libs/libft/libft.h"
# include "../../libs/libft/ft_printf/includes/ft_printf.h"
# include "../../libs/libft/gnl/includes/get_next_line.h"

# define WHITESPACE " \t\n\r\v\f"
# define SYMBOLS "|<>$'\""

typedef struct s_token
{
	int				type;
	char			*content;
	struct s_token	*next;
}					t_token;

typedef struct s_command
{
	char				*name;
	char				**args;
	int					argc;
	t_token				*start;
	t_token				*end;
	struct s_command	*next;
}					t_command;

enum e_token_type
{
	COMMAND,
	CMD_ARG,
	FLAG,
	PIPE,
	REDIR_IN,
	REDIR_OUT,
	APPEND,
	HEREDOC
};

// teste para makefile
void	ft_test(void);

#endif