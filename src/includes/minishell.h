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
# include <fcntl.h>
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
typedef enum e_token_type	t_token_type;

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
	int			status;
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
	int				fd_file;
	struct s_token	*next;
	struct s_token	*prev;
};

struct s_command
{
	char				**argv;
	t_token				**redir;
	int					argc;
	int					*fd;
	int					type;
	struct s_command	*left;
	struct s_command	*right;
	struct s_command	*parent;
};

struct s_pid
{
	int				pid;
	struct s_pid	*next;
};

enum e_token_type
{
	WORD,
	OPERATOR
};

enum e_operator_type
{
	PIPE = 1,
	REDIR_IN,
	REDIR_OUT,
	APPEND,
	HEREDOC
};

// signals
void		prepare_signals(void);
// tokenization
int			count_quotes(char *input);
void		skip_whitespace(char *input, int *i);
void		init_token(t_token **tokens);
void		allocate_token(t_token **tokens, char *input, int start, int end);
void		get_quoted_token(char *input, int *i);
void		get_word(char *input, t_token **tokens, int *i);
void		get_operator(char *input, t_token **tokens, int *i);
void		get_token(char *input, t_token **tokens);
int			validate_tokens(t_token *tokens);
void		set_operator_type(t_token **tokens);
void		print_tokens(t_token *tokens);
// get envs
char		**get_env(char **envp);
char		*env(char *env_name, char **envp);
char		**get_paths(char **env);
// bultins
int			pwd(void);
int			change_dir(char **path, t_minishell *minishell);
int			unset(const char **key, char **envp, t_minishell *minishell);
int			export(char **args, char ***env, t_minishell *minishell);
int			print_order_env(char **env);
int			echo(char **args);
int			exit_builtin(char **args, t_minishell *minishell);
int			is_builtin(char **command, t_minishell *minishell);
// expansor
char		*expand_simple_quotes(char **word);
char		*expand_double_quotes(char **word, t_minishell *minishell);
char		*expand_word(char **word);
char		*expand_vars_and_quotes(char *word, t_minishell *minishell);
char		*expand_env(char *var, char **envp);
char		*expand_path(char **word, t_minishell *minishell);
char		*join_word(char *word, char *new_word);
// execute commands
// prototype -> 1st version
int			exec_command(char **arrstr, int id, t_minishell *minishell);
char		*verify_path(char *bin, char **path);
int			print_env(char **envp);
void		execute_tree_commands(t_minishell *minishell);
void		execute_single_command(t_minishell *minishell);
// tree functions
t_command	*ft_newtreenode(char **args);
void		ft_treeaddonleft(t_command **treenode, t_command *treenew);
void		ft_treeaddonright(t_command **treenode, t_command *treenew);
char		**ft_generate_argv(t_token *tokens, t_minishell *minishell);
void		ft_generate_tree(t_minishell *minishell);
// utils
void		free_arr(char **arr);
void		sort_arr(char **arr);
void		swap_arr(char **wordA, char **wordB);
int			show_error(char *content, char *error, int num_error);
// free functions
void		free_resources_prompt(t_minishell *minishell);
void		free_token(t_token **tokens);
void		free_all(t_minishell *minishell);

#endif