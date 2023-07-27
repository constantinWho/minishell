/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalbers <jalbers@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/02 13:42:47 by jalbers           #+#    #+#             */
/*   Updated: 2023/07/27 16:32:53 by jalbers          ###   ########.fr       */
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
	if (!str1[i] && !str2[i])
		return (1);
	if (str1[i] == '=' || str2[i] == '=')
		return (1);
	return (0);
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

int	change_env(char **env, char *var, char *new_value)
{
	int	i;

	i = 0;
	while (env[i])
	{
		if (str_match(env[i], var) == 1)
		{
			overwrite_env_value(env, new_value, i);
			return (0);
		}
		i++;
	}
	return (0);
}

int	env_value_exists(char **env, char *var)
{
	int	i;

	i = 0;
	while (env[i])
	{
		if (str_match(env[i], var) == 1)
			return (i);
		i++;
	}
	return (-1);
}

int	add_env_value(char **env, char *var, char *value)
{
	int		i;
	int		j;
	int		k;
	char	**new_env;
	
	new_env = copy_realloc_data(env, 1);
	free_array (env);
	env = new_env;
	i = array_len(env);
	env[i] = malloc((str_len(var) + str_len(value) + 2) * sizeof(char));
	j = 0;
	while (var[j])
	{
		env[i][j] = var[j];
		j++;
	}
	env[i][j++] = '=';
	k = 0;
	while (value[k])
		env[i][j++] = value[k++];
	env[i][j] = '\0';
	env[i + 1] = NULL;
	return (0);
}	
