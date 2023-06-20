/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_management.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalbers <jalbers@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 15:54:21 by jalbers           #+#    #+#             */
/*   Updated: 2023/06/20 15:56:21 by jalbers          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	create_forks(int *pids, int pipe_total)
{
	int	i;

	i = 0;
	while (i < pipe_total)
	{
		pids[i] = fork();
		if (pids[i] == -1)
		{
			printf("Error: forking");
			return (1);
		}
		if (pids[i] == 0)
		{
			printf("%i\n", i);
			break;
		}
		i++;
	}
	return (i);
}

int	create_pipes(int pipes[][2], int process_total)
{
	int	i;

	i = 0;
	while (i < process_total)
	{
		if (pipe(pipes[i]) == -1)
		{
			printf("Error opening pipes\n");
			return (1);
		}
		i++;
	}
	printf("Created %i pipes\n", i);
	return (0);
}

int	close_unused_pipe_ends(int pipes[][2], int process_total, int process_index)
{
	int	i;

	i = 0;
	while (i < process_total)
	{
		if (i != process_index || process_index == 0)
			close(pipes[i][0]);
		if (i != process_index + 1)
			close(pipes[i][1]);
		i++;
	}
	return (0);
}

int	create_and_run_processes(char *input, int pipe_total)
{
	int 	pipes[pipe_total + 1][2];
	int		process_index;
	int		*pids;
	
	pids = malloc(pipe_total * sizeof(int));
	create_pipes(pipes, pipe_total + 1);
	process_index = create_forks(pids, pipe_total);
	close_unused_pipe_ends(pipes, pipe_total + 1, process_index);	
	run_individual_processes(input, process_index, pipe_total, pipes);
	wait(NULL);
	free(pids);	
	return (0);
}