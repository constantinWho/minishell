/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_split_rest.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chustei <chustei@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/03 20:09:40 by chustei           #+#    #+#             */
/*   Updated: 2023/08/01 18:12:01 by chustei          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	store_str(char *str, char **dest, int *i, int *count)
{
	int	start;
	int	j;

	start = *i;
	while (str[*i] && str[*i] != '$')
		(*i)++;
	if (str[*i] == '$' || !str[*i])
	{
		j = 0;
		dest[*count] = (char *)malloc(sizeof(char *) * (*i - start + 1));
		while (start < *i)
		{
			dest[*count][j] = str[start];
			j++;
			start++;
		}
		dest[*count][j] = '\0';
		(*count)++;
	}
}

void	store_dolar(char *str, char **dest, int *i, int *count)
{
	int	start;
	int	j;

	start = *i;
	(*i)++;
	while (str[*i] && ft_isalnum(str[*i]) == 1 && str[*i] != '$')
		(*i)++;
	if (str[*i] == '$' || ft_isalnum(str[*i]) == 0 || !str[*i])
	{
		j = 0;
		dest[*count] = (char *)malloc(sizeof(char *) * (*i - start + 1));
		while (start < *i)
		{
			dest[*count][j] = str[start];
			j++;
			start++;
		}
		dest[*count][j] = '\0';
		(*count)++;
	}
}

void	store_rest(char *str, char **dest, int *i, int *count)
{
	int	start;
	int	j;

	start = *i;
	while (str[*i] && str[*i] != '$')
		(*i)++;
	if (str[*i] == '$' || !str)
	{
		j = 0;
		dest[*count] = (char *)malloc(sizeof(char *) * (*i - start + 1));
		while (start < *i)
		{
			dest[*count][j] = str[start];
			j++;
			start++;
		}
		dest[*count][j] = '\0';
		(*count)++;
	}
}

char	**get_rest(char *str, char **dest)
{
	int	i;
	int	count;

	count = 0;
	i = 0;
	while (str[i])
	{
		if (str[i] != '$')
			store_str(str, dest, &i, &count);
		else if (str[i] == '$')
			store_dolar(str, dest, &i, &count);
		else if (ft_isalnum(str[i]) == 0)
			store_rest(str, dest, &i, &count);
	}
	dest[count] = NULL;
	return (dest);
}

char	**get_split_rest(char *str)
{
	char	*s_cpy;
	char	**split_rest;
	char	*dup;
	int		last_i;

	dup = NULL;
	last_i = ft_strlen(str) - 1;
	s_cpy = NULL;
	split_rest = NULL;
	if (str[0] == '"' && str[last_i] == '"')
	{
		dup = ft_strtrim(str, "\"");
		s_cpy = ft_strdup(dup);
		free(dup);
	}
	else
		s_cpy = ft_strdup(str);
	split_rest = (char **)malloc(sizeof(char *)
			* (get_split_num_rest(s_cpy) + 1));
	split_rest = get_rest(s_cpy, split_rest);
	free(s_cpy);
	return (split_rest);
}
