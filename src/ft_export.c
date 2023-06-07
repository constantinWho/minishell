/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalbers <jalbers@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/05 13:37:24 by jalbers           #+#    #+#             */
/*   Updated: 2023/06/05 14:09:05 by jalbers          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	print_sorted_env(char **env)
{
	char	**env_copy;

	env_copy = malloc(sizeof(env));

}

int	ft_export(char **args, t_minishell *shell)
{
	if (!args[1])
		print_sorted_env(shell->env);
	
}