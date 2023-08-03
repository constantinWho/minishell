/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env_str.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chustei <chustei@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 13:31:30 by chustei           #+#    #+#             */
/*   Updated: 2023/08/03 11:43:16 by chustei          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

char	*special_return(char *arg)
{
	char	*str;
	char	*tmp;

	str = NULL;
	if (ft_strlen(arg) == 1)
		str = ft_strdup("$");
	else if (!ft_strncmp(arg, "$0", 2))
	{
		tmp = ft_strdup("minishell");
		str = ft_strjoin(tmp, arg + 2);
		free(tmp);
	}
	else if (!ft_strncmp(arg, "$?", 2))
		str = ft_strdup("$EXIT_STATUS");
	else if (ft_isdigit(arg[1]))
		str = ft_strdup(arg + 2);
	return (str);
}

char	*get_env_str(char *arg, char **env)
{
	int		i;
	int		size;
	char	*new_str;

	printf("arg: %s\n", arg);
	i = 0;
	new_str = special_return(arg);
	if (new_str)
		return (new_str);
	while (env[i])
	{
		size = 0;
		while (env[i][size] != '=')
			size++;
		if (!ft_strncmp(arg + 1, env[i], ft_strlen(arg) - 1)
			&& (size_t)size == ft_strlen(arg) - 1)
			new_str = ft_strdup(env[i] + size + 1);
		i++;
	}
	if (new_str == NULL)
		new_str = ft_strdup(arg + ft_strlen(arg));
	return (new_str);
}
