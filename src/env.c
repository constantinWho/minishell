/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalbers <jalbers@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/02 13:42:47 by jalbers           #+#    #+#             */
/*   Updated: 2023/06/05 13:59:00 by jalbers          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	str_match(char *str1, char *str2)
{
	int	i;

	i = 0;
	while (str1[i] && str2[i])
	{
		if (str1[i] != str2[i])
			return (0);
		i++;
	}
	return (1);
}

int	overwrite_env_value(char **env, char *new_value, int i)
{
	int	j;
	int	k;


	j = 0;
	while (env[i][j] != '=')
		j++;
	j++;
	k = 0;
	while (new_value[k])
		env[i][j++] = new_value[k++];
	env[i][j] = '\0';
	return (0);
}

int	change_env(char **env, char *var, char *new_value) {
	int	i;

	i = 0;
	while (env[i])
	{
		if (str_match(env[i], var) == 1)
		{
			overwrite_env_value(env, new_value, i);
			break;
		}
		i++;
	}
	return (0);
}


