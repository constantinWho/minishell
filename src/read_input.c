/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_input.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalbers <jalbers@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/21 11:09:18 by jalbers           #+#    #+#             */
/*   Updated: 2023/06/21 15:03:25 by jalbers          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

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
	int		i;

	new_str = malloc((size + 1) * sizeof(char));
	i = 0;
	while (str[i])
	{
		new_str[i] = str[i];
		i++;
	}
	new_str[i] = '\0';
	free(str);
	return (new_str);
}

char	*resize_input_str(char *input_str, int multiple)
{
	if (multiple == 1)
		return (input_str);
	input_str = ft_realloc(input_str, (multiple * BUFFER_SIZE2));
	return (input_str);
}

char	*get_input_str(char *input_str, int fd_read)
{
	char	*buffer;
	ssize_t	bytes_read;
	int		i;

	buffer = malloc((BUFFER_SIZE2 + 1) * sizeof(char));
	bytes_read = BUFFER_SIZE2;
	i = 1;
	while (bytes_read == BUFFER_SIZE2)
	{
		bytes_read = read(fd_read, buffer, BUFFER_SIZE2);
		buffer[bytes_read] = '\0';
		input_str = resize_input_str(input_str, i++);
		append_buffer(input_str, buffer);
	}
	if (bytes_read == -1)
	{
		printf("Error reading from pipe\n");
		exit (0);
	}
	close (fd_read);
	free (buffer);
	return (input_str);
}

char	*read_input(t_process *process)
{
	char	*input_str;

	if (process->index == 0)
		return (0);
	input_str = malloc(BUFFER_SIZE2 * sizeof(char));
	input_str[0] = '\0';
	input_str = get_input_str(input_str, process->fd_read);
	return (input_str);
}
