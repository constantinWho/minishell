/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_processes.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalbers <jalbers@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 19:16:39 by jalbers           #+#    #+#             */
/*   Updated: 2023/07/05 13:22:24 by jalbers          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	create_forks(int pipe_total)
{
	int	*pids;
	int	i;

	pids = malloc(pipe_total * sizeof(int));
	i = 0;
	while (i < pipe_total)
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
	return (pipe_total - i);
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

char	*get_cmd_str(char *input_str, int process_index)
{
	char	*cmd_str;
	int		cmd_len;
	int		pipe_count;
	int		i;
	int		j;

	pipe_count = 0;
	i = 0;
	while (pipe_count < process_index)
	{
		if (input_str[i] == '|')
			pipe_count++;
		i++;
	}
	cmd_len = i;
	while (input_str[cmd_len] && input_str[cmd_len] != '|')
		cmd_len++;
	cmd_str = malloc((cmd_len - i + 1) * sizeof(char));
	j = 0;
	while (input_str[i] && input_str[i] != '|')
		cmd_str[j++] = input_str[i++];
	cmd_str[j] = '\0';
	return (cmd_str);
}

int	set_pipe_ends(t_process *process, int pipes[][2], int pipe_total)
{
	if (process->index != pipe_total)
	{
		process->fd_write = pipes[process->index + 1][1];
		if (dup2(process->fd_write, 1) == -1) {
            printf("Failed to duplicate file descriptor\n");
            return 1;
        }
	}
	else
		process->fd_write = 1;
	process->fd_read = pipes[process->index][0];
	return (0);
}

t_process	*create_processes(char *input, int pipe_total)
{
	t_process	*process;
	int			pipes[pipe_total + 1][2];

	process = malloc(sizeof(t_process));
	create_pipes(pipes, pipe_total + 1);
	process->index = create_forks(pipe_total);
	process->cmd_str = get_cmd_str(input, process->index);
	process->pipe_total = pipe_total;
	set_pipe_ends(process, pipes, pipe_total);
	close_unused_pipe_ends(pipes, pipe_total + 1, process->index);
	return (process);
}

int	destroy_processes(t_process *process)
{
	free(process->cmd_str);
	if (process->index != 0)
		free(process->pipe_input);
	if (process->index != process->pipe_total)
	{
		free(process);
		exit(0);
	}	
		free(process);
	return (0);
}
