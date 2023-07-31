/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalbers <jalbers@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/05 13:37:24 by jalbers           #+#    #+#             */
/*   Updated: 2023/07/31 17:23:21 by jalbers          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	ft_export(char **args, t_minishell *shell)
{
	// char	**new_env;
	char	*new_value;

	if (!args[1])
	{
		print_sorted_env(shell->env);
		return (0);
	}
	if (args[2] && args[3])
		new_value = args[3];
	else
		new_value = "";
	if (env_value_exists(shell->env, args[1]) != -1)
		change_env(shell->env, args[1], new_value);
	else
	{
		// new_env = copy_realloc_data(shell->env, 1);
		// free_array(shell->env);
		// shell->env = new_env;
		shell->env = add_env_value(shell->env, args[1], new_value);
	}
	return (0);
}
