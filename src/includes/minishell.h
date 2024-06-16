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
# include <sys/stat.h>
# include <signal.h>
# include <termios.h>
# include <string.h>
# include <fcntl.h>
# include <errno.h>
# include <sys/types.h>
# include <dirent.h>

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
	int			stdin_backup;
	int			stdout_backup;
	t_token		*tokens;
	t_command	*tree_cmd;
	t_list		*pid_list;
};

struct s_token
{
	int				type;
	char			*content;
	struct s_token	*next;
	struct s_token	*prev;
};

struct s_command
{
	char				**argv;
	t_token				*redir;
	int					argc;
	int					fd[2];
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
void		handle_signal(int signum);
void		handle_signal_exec(int signum);
// status
int			control_status(int status);
int			filter_status(int status);
// tokenization
int			count_quotes(char *input);
void		skip_whitespace(char *input, int *i);
void		init_token(t_token **tokens);
void		ft_tokenadd_back(t_token **lst, t_token *new);
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
char		**get_paths(char **env);
char		*get_single_env(char *env_name, char **envp);
// bultins
int			pwd(void);
int			change_dir(char **path, t_minishell *minishell);
int			unset(const char **key, t_minishell *minishell);
int			export(char **args, t_minishell *minishell);
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
// redirections
t_token		*ft_generate_redirs(t_token **token, t_minishell *minishell);
void		add_redir(t_token **rds, t_token *new_rd, t_minishell *minishell);
int			setup_redirs(t_token *redir);
int			redirect_input(char *filename);
int			redirect_output(char *filename);
int			append_output(char *filename);
int			heredoc(char **str, int index);
int			verify_heredoc(t_minishell *minishell);
void		reset_fds(t_minishell *minishell);
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
void		close_fds(t_minishell *minishell);
// utils
void		free_arr(char **arr);
void		sort_arr(char **arr);
void		swap_arr(char **wordA, char **wordB);
int			show_error(char *content, char *error, int num_error);
// free functions
void		free_resources_prompt(t_minishell *minishell);
void		free_token(t_token **tokens);
void		free_all(t_minishell *minishell);
void		free_tree(t_command **tree);
void		free_list(t_list **list);

#endif