/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chustei <chustei@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/02 13:42:47 by jalbers           #+#    #+#             */
/*   Updated: 2023/08/02 15:44:04 by chustei          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	str_match(char *str1, char *str2)
{
	int	i;

	i = 0;
	if (!str1)
		return (1);
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

char	**add_env_value(char **env, char *var, char *value)
{
	int		i;
	int		j;
	int		k;
	char	**new_env;

	new_env = copy_realloc_data(env, 1);
	free_array (env);
	i = array_len(new_env);
	new_env[i] = malloc((str_len(var) + str_len(value) + 2) * sizeof(char));
	j = 0;
	while (var[j])
	{
		new_env[i][j] = var[j];
		j++;
	}
	new_env[i][j++] = '=';
	k = 0;
	while (value[k])
		new_env[i][j++] = value[k++];
	new_env[i][j] = '\0';
	new_env[i + 1] = NULL;
	return (new_env);
}
