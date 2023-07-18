/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chustei <chustei@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/07 12:03:32 by chustei           #+#    #+#             */
/*   Updated: 2023/07/18 16:53:53 by chustei          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include "../lib/libft/inc/libft.h"

# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/wait.h>
# include <signal.h>
# include <unistd.h>
# include <stdlib.h>

// Type of the node (e.g., "command", "redirection")
// Value associated with the node (e.g., command name, file name)
// Array of child nodes
// Number of child nodes

# ifndef BUFFER_SIZE2
#  define BUFFER_SIZE2 4
# endif

enum e_token
{
	T_SPACE,
	T_WORD,
	T_2Q_WORD,
	T_1Q_WORD,
	T_PIPE,
	T_REDIR_OUT,
	T_REDIR_OUT_APPEND,
	T_REDIR_IN,
	T_HEREDOC,
};

typedef struct s_redir
{
	char					*redir;
	char					*arg;
	struct s_redir			*next;
}	t_redir;

typedef struct s_group
{
	char			*cmd;
	char			**args;
	t_redir			*redirs;
	struct s_group	*next;
}	t_group;

typedef struct s_process
{
	int				index;
	char			*cmd_str;
	char			*pipe_input;
	int				fd_read;
	int				fd_write;
	int				pipe_total;
}	t_process;

typedef struct s_token
{
	char			*value;
	enum e_token	type;
	struct s_token	*next;
}	t_token;

typedef struct s_minishell {
	t_token	*tokens;
	t_group	*groups;
	char	**args;
	char	**env;
}	t_minishell;

int			ft_cd(char **args, t_minishell *shell);
int			change_env(char **env, char *var, char *new_value);
int			str_match(char *str1, char *str2);
int			ft_echo(char **args);
int			ft_pwd(void);
int			ft_export(char **args, t_minishell *shell);
int			array_len(char **array);
int			str_len(char *str);
int			compare_ascii(char *str1, char *str2);
int			free_array(char **array);
int			add_env_value(char **env, char *var, char *value);
int			env_value_exists(char **env, char *var);
int			print_sorted_env(char **env);
char		**copy_realloc_data(char **src, int added);
int			ft_env(t_minishell *shell);
int			ft_unset(char **args, t_minishell *shell);
void		ft_lexer(t_minishell *shell, char *input);
void		ignore_signal_for_shell(void);
t_process	*create_processes(char *input, int pipe_total);
int			destroy_processes(t_process *process);
char		*read_input(t_process *process);
int			count_strs(char *s);
int			skip_whitespace(char *s, int i);
int			is_delimiter(char c);
void		special_split(t_minishell *shell, char *s);
void		append_token(t_minishell *shell, char *arg);
t_token		*create_token(char *str, enum e_token type);
void		free_tokens(t_token *lst);
void		word_butcher(t_minishell *shell, char *word);
void		add_new_token(t_minishell *shell, t_token *new_token);
char		**word_split(char *str, int words_count);
void		word_butcher(t_minishell *shell, char *word);
int			get_words_count(char *str);
int			check_quotes(char *input);
void		parser(t_minishell *shell);
void		find_cmd(t_token **tokens, t_group *new_group);
int			is_redirection(t_token *token);
void		skip_redirection(t_token **cur_token);
int			is_valid_word_token(t_token *token);
int			starts_with_dollar(t_token *token);
void		find_args(t_token **tokens, t_group *new_group);
void		update_prev_token_next(t_token **prev_token, t_token **cur_token);
void		update_tokens_head(t_token **tokens, t_token **cur_token);
void		skip_redir_block_update_prev_token(t_token **cur_token,
				t_token **prev_token);
void		find_redirs(t_token **tokens, t_group *new_group);
void		add_group(t_token *tokens, t_group **groups);
int			check_if_first_pipe(t_token *tokens);
void		delete_first_space_if_exists(t_token **head);
void		delete_pipe_if_exists(t_token **head);

#endif
