/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_individual_processes.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalbers <jalbers@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 15:57:39 by jalbers           #+#    #+#             */
/*   Updated: 2023/06/20 16:00:28 by jalbers          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"


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

char	*fill_pipe_input(char *pipe_input, int pipes[][2], int process_index)
{
	char	*buffer;
	ssize_t	bytes_read;
	int		i;
	
	if (process_index == 0)
		return (0);
	buffer = malloc((BUFFER_SIZE + 1) * sizeof(char));
	bytes_read = read(pipes[process_index][0], buffer, BUFFER_SIZE);
	i = 1;	
	while (bytes_read > 0)
	{
		if (i > 1)
			pipe_input = ft_realloc(pipe_input, (i * BUFFER_SIZE));
			// pipe_input = realloc(pipe_input, (i * BUFFER_SIZE));
		append_buffer(pipe_input, buffer);
		bytes_read = read(pipes[process_index][0], buffer, BUFFER_SIZE);
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
	pipe_input = malloc(BUFFER_SIZE * sizeof(char));
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