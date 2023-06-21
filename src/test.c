/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalbers <jalbers@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 17:03:51 by jalbers           #+#    #+#             */
/*   Updated: 2023/06/20 17:44:34 by jalbers          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>



// const int	BUFFER_SIZE2 = 4;

// int	str_len(char *str)
// {
// 	int	i;

// 	i = 0;
// 	while (str[i])
// 		i++;
// 	return (i);
// }

int	count_pipes(char *input_str)
{
	int	pipe_count;
	int	i;

	pipe_count = 0;
	i = 0;
	while (input_str[i])
	{
		if (input_str[i] == '|')
			pipe_count++;
		i++;
	}
	return (pipe_count);
}

int	fill_cmd_str(char *input_str, char *cmd_str, int process_index)
{
	int	pipe_count;
	int	i;
	int	j;

	pipe_count = 0;
	i = str_len(cmd_str);
	while (pipe_count < process_index)
	{
		if (input_str[i] == '|')
			pipe_count++;
		i++;
	}
	j = 0;
	while (input_str[i] && input_str[i] != '|')
		cmd_str[j++] = input_str[i++];
	cmd_str[j] = '\0';
	return (0);
}

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

int	get_cmd_length(char *input_str, int process_number)
{
	int	pipe_count;
	int	i;
	int	cmd_length;

	pipe_count = 0;
	i = 0;
	while (pipe_count < process_number && input_str[i])
	{
		if (input_str[i] == '|')
			pipe_count++;
		i++;
	}
	cmd_length = 0;
	while (input_str[i] != '|' && input_str[i])
	{
		cmd_length++;
		i++;
	}
	return (cmd_length);
}

int	append_buffer(char *str, char *buffer)
{
	int	i;
	int	j;

	i = 0;
	while (str[i])
		i++;
	j = 0;
	while (buffer[j])
	{
		str[i++] = buffer[j++];
	}
	str[i] = '\0';
	return (0);
}

char	*ft_realloc(char *str, int size)
{
	char	*new_str;
	char	*old_str;
	int		i;

	old_str = str;
	new_str = malloc((size + 1) * sizeof(char));
	i = 0;
	while (str[i])
	{
		new_str[i] = str[i];
		i++;
	}
	new_str[i] = '\0';
	str = new_str;
	free (old_str);
	return (str);
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

char	*fill_pipe_input(char *pipe_input, int pipes[][2], int process_index)
{
	char	*buffer;
	ssize_t	bytes_read;
	int		i;
	
	if (process_index == 0)
		return (0);
	buffer = malloc((BUFFER_SIZE2 + 1) * sizeof(char));
	bytes_read = read(pipes[process_index][0], buffer, BUFFER_SIZE2);
	i = 1;	
	while (bytes_read > 0)
	{
		if (i > 1)
			pipe_input = ft_realloc(pipe_input, (i * BUFFER_SIZE2));
			// pipe_input = realloc(pipe_input, (i * BUFFER_SIZE2));
		append_buffer(pipe_input, buffer);
		bytes_read = read(pipes[process_index][0], buffer, BUFFER_SIZE2);
		i++;
	}
	if (bytes_read == -1)
	{
		printf("Error reading from pipe\n");
		exit (0);
	}
	close (pipes[process_index][0]);
	free (buffer);
	return (pipe_input);
}

int	run_process_and_pipe_output(int process_index, int total_pipes, int pipes[][2], char* cmd_str)
{
	if (process_index == total_pipes)
		return (0);
	if (write(pipes[process_index + 1][1], cmd_str, str_len(cmd_str) + 1) == -1)
	{
		printf("Error writing to pipe, Process Index:%i\n", process_index);
		return (1);
	}
	close(pipes[process_index + 1][1]);
	return (0);
}

int	run_individual_processes(char *input, int process_index, int pipe_total, int pipes[][2])
{
	char	*cmd_str;
	char	*pipe_input;

	cmd_str = malloc((get_cmd_length(input, process_index) + 1) * sizeof(char));
	pipe_input = malloc(BUFFER_SIZE2 * sizeof(char));
	fill_cmd_str(input, cmd_str, process_index);
	pipe_input = fill_pipe_input(pipe_input, pipes, process_index);
	
	// run_parser(cmd_str, pipe_input) - 
	run_process_and_pipe_output(process_index, pipe_total, pipes, cmd_str);	
	// char *result = parser(cmd_str, pipe_input, fd_stout);
	
	printf("Word:%s, Process Index:%i, prevOutput:%s\n", cmd_str, process_index, pipe_input);
	free (pipe_input);
	free (cmd_str);
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

// int main()
// {
// 	char	*input	= "Hello | how | are | you";

// 	int		pipe_total = count_pipes(input);
// 	create_and_run_processes(input, pipe_total);
// 	return (0);
// }
