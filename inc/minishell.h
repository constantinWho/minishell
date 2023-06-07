/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalbers <jalbers@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 15:52:26 by chustei           #+#    #+#             */
/*   Updated: 2023/06/05 13:38:21 by jalbers          ###   ########.fr       */
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

