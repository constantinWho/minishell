/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalbers <jalbers@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 17:01:21 by jalbers           #+#    #+#             */
/*   Updated: 2023/07/05 18:31:36 by jalbers          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	ft_unset(char **args, t_minishell *shell)
{
	char	**env;
	char	*lost_str;
	int		i;

	env = shell->env;
	i = 0;
	while (env[i] && str_match(env[i], args[2]) == 0)
		i++;
	lost_str = env[i];
	while (env[i] && env[i + 1])
	{
		env[i] = env[i + 1];
		i++;
	}
	env[i] = NULL;
	free(lost_str);
	return (0);
}
