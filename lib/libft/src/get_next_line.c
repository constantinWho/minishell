/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chustei <chustei@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/03 16:36:18 by chustei           #+#    #+#             */
/*   Updated: 2023/03/02 13:03:01 by chustei          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"

char	*ft_strjoin_void(char *s1, char *s2)
{
	size_t	i;
	size_t	j;
	char	*str;

	if (!s1)
	{
		s1 = (char *)malloc(1 * sizeof(char));
		s1[0] = '\0';
	}
	if (!s1 || !s2)
		return (NULL);
	str = malloc((ft_strlen(s1) + ft_strlen(s2) + 1) * sizeof(char));
	if (str == NULL)
		return (NULL);
	i = -1;
	j = 0;
	if (s1)
		while (s1[++i])
			str[i] = s1[i];
	while (s2[j])
		str[i++] = s2[j++];
	str[ft_strlen(s1) + ft_strlen(s2)] = '\0';
	free(s1);
	return (str);
}

char	*ft_line(char *storage)
{
	int		i;
	char	*str;

	i = 0;
	if (!storage[i])
		return (NULL);
	while (storage[i] && storage[i] != '\n')
		i++;
	str = (char *)malloc(sizeof(char) * (i + 2));
	if (!str)
		return (NULL);
	i = 0;
	while (storage[i] && storage[i] != '\n')
	{
		str[i] = storage[i];
		i++;
	}
	if (storage[i] == '\n')
	{
		str[i] = storage[i];
		i++;
	}
	str[i] = '\0';
	return (str);
}

char	*ft_save(char *storage)
{
	int		i;
	int		pos;
	char	*str;

	i = 0;
	while (storage[i] && storage[i] != '\n')
		i++;
	if (!storage[i])
	{
		free(storage);
		return (NULL);
	}
	str = (char *)malloc(sizeof(char) * (ft_strlen(storage) - i + 1));
	if (!str)
	{
		free(str);
		return (NULL);
	}
	i++;
	pos = 0;
	while (storage[i])
		str[pos++] = storage[i++];
	str[pos] = '\0';
	free(storage);
	return (str);
}

char	*ft_read_storage(int fd, char *storage)
{
	char	*buff;
	int		bytes;

	buff = malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!buff)
		return (NULL);
	bytes = 1;
	while (!ft_strchr(storage, '\n') && bytes != 0)
	{
		bytes = read(fd, buff, BUFFER_SIZE);
		if (bytes == -1)
		{
			free(buff);
			free(storage);
			return (NULL);
		}
		buff[bytes] = '\0';
		storage = ft_strjoin_void(storage, buff);
	}
	free(buff);
	return (storage);
}

char	*get_next_line(int fd)
{
	char		*line;
	static char	*storage[5000];

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (0);
	storage[fd] = ft_read_storage(fd, storage[fd]);
	if (!storage[fd])
		return (NULL);
	line = ft_line(storage[fd]);
	storage[fd] = ft_save(storage[fd]);
	return (line);
}
/*
#include <fcntl.h>
#include <stdio.h>
int	main(void)
{
	char	*line1;
	char	*line2;
	int		i;
	int		fd1;
	int		fd2;


	fd1 = open("test.txt", O_RDONLY);
	fd2 = open("test1.txt", O_RDONLY);
	i = 1;
	while (i < 10)
	{
		line1 = get_next_line(fd1);
		line2 = get_next_line(fd2);
		printf("line[%i] file1: %s\n", i, line1);
		printf("line[%i]file2: %s\n", i, line2);
		i++;
	}
	close(fd1);
	return (0);
}
 */
