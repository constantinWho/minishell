/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalbers <jalbers@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/05 13:37:24 by jalbers           #+#    #+#             */
/*   Updated: 2023/06/12 16:03:12 by jalbers          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

// This function assumes arg1 is var name and arg2 is var value.
int	ft_export(char **args, t_minishell *shell)
{
	char	**new_env;

	if (!args[1])
		print_sorted_env(shell->env);
	else if (args[1] && args[2])
	{
		if (env_value_exists(shell->env, args[1]) == 1)
			change_env(shell->env, args[1], args[2]);
		else
		{
			new_env = copy_realloc_data(shell->env, 1);
			free_array(shell->env);
			shell->env = new_env;
			add_env_value(shell->env, args[1], args[2]);
		}
	}
	// else if (!args[2]) -> export my_value -> 
	return (0);
}
