/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chustei <chustei@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/07 12:03:32 by chustei           #+#    #+#             */
/*   Updated: 2023/06/07 12:03:36 by chustei          ###   ########.fr       */
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

// Type of the node (e.g., "command", "redirection")
// Value associated with the node (e.g., command name, file name)
// Array of child nodes
// Number of child nodes
typedef struct s_tree
{
	char			*type;
	char			*value;
	struct s_tree	**children;
	int				num_children;
}	t_tree;

typedef struct s_token
{
	int				len;
	char			*str;
	char			*type;
	struct s_token	*next;
}	t_token;

typedef struct s_minishell {
	t_token	*head;
	char	**env;
}	t_minishell;

int	ft_cd(char **args, t_minishell *shell);
int	change_env(char **env, char *var, char *new_value);
int	str_match(char *str1, char *str2);
int	ft_echo(char **args);
int	ft_pwd(void);
int	ft_export(char **args, t_minishell *shell);
#endif

