/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_processes.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: josephalbers <josephalbers@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 19:16:39 by jalbers           #+#    #+#             */
/*   Updated: 2023/08/03 15:25:03 by josephalber      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	create_forks(int total_new_processes)
{
	int	*pids;
	int	i;

	pids = malloc(total_new_processes * sizeof(int));
	i = 0;
	while (i < total_new_processes)
	{
		pids[i] = fork();
		if (pids[i] == -1)
		{
			printf("Error: forking");
			return (1);
		}
		if (pids[i] != 0)
			break ;
		i++;
	}
	free(pids);
	return (total_new_processes - i);
}

int	create_pipes(int **pipes, int process_total)
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
	return (0);
}

int	close_unused_pipe_ends(int **pipes, int process_total, int process_index)
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

int	set_pipe_ends(t_process *process, int **pipes, int process_total)
{
	if (process->index != process_total - 1)
		process->fd_write = pipes[process->index + 1][1];
	else
		process->fd_write = 1;
	process->fd_read = pipes[process->index][0];
	return (0);
}

t_process	*create_processes(int process_total)
{
	t_process	*process;
	int			**pipes;

	pipes = malloc_pipes(process_total);
	process = malloc(sizeof(t_process));
	create_pipes(pipes, process_total);
	process->index = create_forks(process_total - 1);
	process->pipe_total = process_total - 1;
	set_pipe_ends(process, pipes, process_total);
	close_unused_pipe_ends(pipes, process_total, process->index);
	free_pipes(pipes, process_total);
	return (process);
}
