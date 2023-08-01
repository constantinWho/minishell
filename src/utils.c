/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chustei <chustei@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/07 13:32:13 by jalbers           #+#    #+#             */
/*   Updated: 2023/08/01 18:12:10 by chustei          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	array_len(char **array)
{
	int	i;

	i = 0;
	while (array[i])
		i++;
	return (i);
}

int	str_len(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

int	compare_ascii(char *str1, char *str2)
{
	int	i;

	i = 0;
	while (str1[i] && str2[i] && str1[i] == str2[i])
		i++;
	if (!str1[i] || str1[i] < str2[i])
		return (1);
	return (0);
}

int	free_array(char **array)
{
	int	i;

	i = 0;
	if (!array)
		return (0);
	while (array[i])
	{
		free(array[i]);
		i++;
	}
	free (array);
	return (0);
}

char	**copy_realloc_data(char **src, int added)
{
	char	**dest;
	int		i;
	int		j;

	dest = malloc((array_len(src) + 1 + added) * sizeof(*src));
	i = 0;
	while (src[i])
	{
		j = 0;
		dest[i] = malloc((str_len(src[i]) + 1) * sizeof(**src));
		while (src[i][j])
		{
			dest[i][j] = src[i][j];
			j++;
		}
		dest[i][j] = '\0';
		i++;
	}
	dest[i] = NULL;
	return (dest);
}
