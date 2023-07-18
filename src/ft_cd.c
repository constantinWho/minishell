/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalbers <jalbers@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 16:54:52 by chustei           #+#    #+#             */
/*   Updated: 2023/07/05 18:15:21 by jalbers          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

// needs functionality for "cd -" takes user back to previous position
// this is stored in the .env file

char	*ft_getenv(char **env, char *var)
{
	int	i;

	i = 0;
	while (env[i])
	{
		if (str_match(env[i], var) == 1)
			break;
		i++;
	}
	if (!env[i])
		return (0);
	return (&env[i][str_len(var) + 1]);
}

int	ft_cd(char **args, t_minishell *shell)
{
	char	updated_dir[500];

	if (!args[1])
		chdir(getenv("HOME"));
	else if (str_match(args[2], "-"))
		chdir(ft_getenv(shell->env, "OLDPWD"));
	else
		chdir(args[2]);
	change_env(shell->env, "OLDPWD", ft_getenv(shell->env, "PWD"));
	if (getcwd(updated_dir, sizeof(updated_dir)) == NULL)
	{
		perror("getcwd() error");
		return (1);
	}
	change_env(shell->env, "PWD", updated_dir);
	return (0);
}
