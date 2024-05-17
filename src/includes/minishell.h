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
# include <signal.h>
# include <termios.h>
# include <string.h>
# include <errno.h>

# include "../../libs/libft/libft.h"
# include "../../libs/libft/ft_printf/includes/ft_printf.h"
# include "../../libs/libft/gnl/includes/get_next_line.h"

# define WHITESPACE " \t\n\r\v\f"
# define SYMBOLS "|<>"
# define QUOTES "'\""

typedef struct s_minishell	t_minishell;
typedef struct s_token		t_token;
typedef struct s_command	t_command;
typedef struct s_pid		t_pid;

/*
*	@input = input da linha de comando
*	@envp = variáveis de ambiente
*	@path = paths dos executáveis
*	@tokens = lista de tokens
*	@tree_cmd = arvore de comandos
*	@arr_pid = array para guardar pids
*	@arr_pid_size = tamanho do array de pids
*/
struct s_minishell
{
	char		*input;
	char		**envp;
	char		**path;
	t_token		*tokens;
	t_command	*tree_cmd;
	t_list		*pid_list;
};

struct s_token
{
	int				type;
	char			*content;
	struct s_token	*next;
};

struct s_command
{
	char				*name;
	char				**args;
	int					argc;
	t_token				*start;
	t_token				*end;
	struct s_command	*left;
	struct s_command	*right;
};

struct s_pid
{
	int				pid;
	struct s_pid	*next;
};

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
	ENV,
	STATUS
};

// signals
void	prepare_signals(void);
// tokenization
/*count quotes*/
int		count_quotes(char *input);
void	skip_whitespace(char *input, int *i);
void	init_token(t_token **tokens);
void	allocate_token(t_token **tokens, char *input, int start, int end);
void	get_quoted_token(char *input, t_token **tokens, int *i);
void	get_word_token(char *input, t_token **tokens, int *i);
void	get_special_token(char *input, t_token **tokens, int *i);
void	get_env_token(char *input, t_token **tokens, int *i);
void	get_token(char *input, t_token **tokens);
void	free_token(t_token **tokens);
// get envs
char	**get_env(char **envp);
char	**get_paths(char **env);
// bultins
int		pwd(void);
int		change_dir(char *path);
int		unset(const char *key, char **envp);
int		export(char *variable, char ***env);
int		print_order_env(char **env);
int		echo(char **args);
int		is_builtin(char **command, char **env);
// execute commands
// prototype -> 1st version
int		exec_command(char **arrstr, int id, t_minishell *minishell);
char	*verify_path(char *bin, char **path);
int		print_env(char **envp);
// utils
void	free_arr(char **arr);
void	sort_arr(char **arr);
void	swap_arr(char **wordA, char **wordB);

#endif