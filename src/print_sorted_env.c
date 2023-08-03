/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_sorted_env.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chustei <chustei@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 13:24:07 by jalbers           #+#    #+#             */
/*   Updated: 2023/08/03 12:01:44 by chustei          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	merge(char **array, int start, int mid, int end)
{
	char	**sorted_array;
	int		i;
	int		j;
	int		k;

	sorted_array = malloc((end - start + 2) * sizeof(char *));
	i = 0;
	j = start;
	k = mid + 1;
	while (i <= end - start)
	{
		if (k > end || (compare_ascii(array[j], array[k]) == 1 && j <= mid))
			sorted_array[i] = array[j++];
		else
			sorted_array[i] = array[k++];
		i++;
	}
	sorted_array[i] = NULL;
	i = 0;
	while (start <= end)
		array[start++] = sorted_array[i++];
	free (sorted_array);
	return (0);
}

int	merge_sort_array(char **array, int start, int end)
{
	int	mid;

	mid = (start + end) / 2;
	if (start < end - 1)
	{
		merge_sort_array(array, start, mid);
		merge_sort_array(array, mid + 1, end);
	}
	if (start != end)
		merge(array, start, mid, end);
	return (0);
}

int	print_sorted_env(char **env)
{
	char	**env_copy;
	int		env_length;
	int		i;

	env_length = array_len(env);
	env_copy = copy_realloc_data(env, 0);
	i = 0;
	merge_sort_array(env_copy, 0, env_length - 1);
	i = 0;
	while (env_copy[i])
	{
		printf("declare -x %s\n", env_copy[i]);
		i++;
	}
	free_array(env_copy);
	return (0);
}
