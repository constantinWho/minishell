/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalbers <jalbers@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/07 12:03:32 by chustei           #+#    #+#             */
/*   Updated: 2023/06/13 13:40:21 by jalbers          ###   ########.fr       */
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
typedef struct s_group
{
	char			*type;
	char			*value;
	struct s_tree	**children;
	int				num_children;
	struct s_group	*next;
}	t_group;

typedef struct s_token
{
	int				len;
	char			*str;
	char			*type;
	struct s_token	*next;
}	t_token;

typedef struct s_minishell {
	t_token	*tokens;
	t_group	*tree;
	char	**args;
	char	**env;
}	t_minishell;

int		ft_cd(char **args, t_minishell *shell);
int		change_env(char **env, char *var, char *new_value);
int		str_match(char *str1, char *str2);
int		ft_echo(char **args);
int		ft_pwd(void);
int		ft_export(char **args, t_minishell *shell);
int		array_len(char **array);
int		str_len(char *str);
int		compare_ascii(char *str1, char *str2);
int		free_array(char **array);
int		add_env_value(char **env, char *var, char *value);
int		env_value_exists(char **env, char *var);
int		print_sorted_env(char **env);
char	**copy_realloc_data(char **src, int added);
int		ft_env(t_minishell *shell);
int		ft_unset(char **args, t_minishell *shell);
void	ft_lexer(t_minishell *shell, char *input);
void	ignore_signal_for_shell(void);

#endif

