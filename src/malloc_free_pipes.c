/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc_free_pipes.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chustei <chustei@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/31 17:44:21 by jalbers           #+#    #+#             */
/*   Updated: 2023/08/01 18:15:36 by chustei          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	**malloc_pipes(int process_total)
{
	int	**pipes;
	int	i;

	pipes = malloc((process_total) * sizeof(int *));
	i = 0;
	while (i < process_total)
	{
		pipes[i] = malloc(2 * sizeof(int));
		i++;
	}
	return (pipes);
}

void	free_pipes(int **pipes, int process_total)
{
	int	i;

	i = 0;
	while (i < process_total)
		free(pipes[i++]);
	free(pipes);
}
