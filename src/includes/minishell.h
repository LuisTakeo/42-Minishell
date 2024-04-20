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
# include <sys/types.h>
# include <sys/wait.h>

# include "../../libs/libft/libft.h"
# include "../../libs/libft/ft_printf/includes/ft_printf.h"
# include "../../libs/libft/gnl/includes/get_next_line.h"

# define WHITESPACE " \t\n\r\v\f"
# define SYMBOLS "|<>$"
# define QUOTES "'\""

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
	HEREDOC,
	ENVAR
};

// teste para makefile
void	ft_test(void);

// tokenization
int		count_quotes(char *input);
void	skip_whitespace(char *input, int *i);
void	init_token(t_token **tokens);
void	allocate_token(t_token **tokens, char *input, int start, int end);
void	get_quoted_token(char *input, t_token **tokens, int *i);
void	get_word_token(char *input, t_token **tokens, int *i);
void	get_special_token(char *input, t_token **tokens, int *i);
void	get_token(char *input, t_token **tokens);
void	free_token(t_token **tokens);
// get envs
t_list	*get_env(char **envp);
char	**get_paths(char **env);
// execute commands
// prototype -> 1st version
void	exec_command(char **arrstr, int id, char **env, char **path);

#endif