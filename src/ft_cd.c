/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalbers <jalbers@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 16:54:52 by chustei           #+#    #+#             */
/*   Updated: 2023/06/12 17:25:43 by jalbers          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

// needs functionality for "cd -" takes user back to previous position
// this is stored in the .env file
int	ft_cd(char **args, t_minishell *shell)
{
	char	updated_dir[500];

	if (!args[1])
		chdir(getenv("HOME"));
	else if (str_match(args[1], "-"))
		chdir(getenv("OLDPWD"));
	else
		chdir(args[1]);
	change_env(shell->env, "OLDPWD", getenv("PWD"));
	if (getcwd(updated_dir, sizeof(updated_dir)) == NULL)
	{
		perror("getcwd() error");
		return (1);
	}
	change_env(shell->env, "PWD", updated_dir);
	return (0);
}
