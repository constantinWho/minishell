/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: josephalbers <josephalbers@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 16:54:52 by chustei           #+#    #+#             */
/*   Updated: 2023/07/26 21:04:35 by josephalber      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

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

int	check_if_directory_exists(char *full_path)
{
	DIR *dir;

	dir = opendir(full_path);
	if (dir == NULL)
	{
		perror("cd");
		return 0;
	}
	return (1);
}

int	ft_cd(char **args, t_minishell *shell)
{
	char	updated_dir[500];

	if (!args[1])
		chdir(getenv("HOME"));
	else if (str_match(args[1], "-"))
		chdir(ft_getenv(shell->env, "OLDPWD"));
	else if (check_if_directory_exists(args[1]) == 0)
		return (1);
	else
		chdir(args[1]);
	change_env(shell->env, "OLDPWD", ft_getenv(shell->env, "PWD"));
	if (getcwd(updated_dir, sizeof(updated_dir)) == NULL)
	{
		perror("getcwd() error");
		return (1);
	}
	change_env(shell->env, "PWD", updated_dir);
	return (0);
}
