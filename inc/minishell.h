/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chustei <chustei@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 15:52:26 by chustei           #+#    #+#             */
/*   Updated: 2023/05/25 16:33:50 by chustei          ###   ########.fr       */
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
}	t_minishell;

int	ft_cd(char **args);

#endif
