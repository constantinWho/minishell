/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalbers <jalbers@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 17:01:21 by jalbers           #+#    #+#             */
/*   Updated: 2023/06/12 17:28:02 by jalbers          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	ft_unset(char **args, t_minishell *shell)
{
	char	**env;
	int		i;

	env = shell->env;
	i = 0;
	while (env[i] && str_match(env[i], args[1]) == 0)
		i++;
	while (env[i] && env[i + 1])
	{
		env[i] = env[i + 1];
		i++;
	}
	env[i] = NULL;
	return (0);
}
