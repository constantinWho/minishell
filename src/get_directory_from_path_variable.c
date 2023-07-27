/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_directory_from_path_variable.c                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalbers <jalbers@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/27 12:06:42 by jalbers           #+#    #+#             */
/*   Updated: 2023/07/27 12:22:37 by jalbers          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	count_directories(char *path_string)
{
	int	count;
	int	i;

	count = 0;
	i = 0;
	while (path_string[i])
	{
		if (path_string[i] == ':')
			count++;
		i++;
	}
	return(count);
}

int	get_directory_length(char *path_var, int index)
{
	int	length;

	length = 0;
	while (path_var[index] && path_var[index] != ':')
	{
		length++;	
		index++;
	}
	return (length);
}

int	get_start_index_of_directory(char *path_var, int number)
{
	int	count;
	int	i;
	
	i = 5;
	count = 0;
	while (count != number)
	{
		if (path_var[i] == ':')
			count++;
		i++;
	}
	return (i);
}

char	*get_directory_by_number(char *path_var, int	number)
{
	char	*directory;
	int		directory_length;
	int 	i;
	int		j;

	i = get_start_index_of_directory(path_var, number);
	directory_length = get_directory_length(path_var, i) + 2;
	directory = malloc(directory_length * sizeof(char));
	j = 0;
	while (path_var[i] && path_var[i] != ':')
		directory[j++] = path_var[i++];
	directory[j++] = '/';
	directory[j] = '\0';
	return (directory);
}

char	*get_correct_directory(char *str, char **env)
{
	int		env_path_index;
	char	*path_var;
	char	*directory_path;
	int		i;
	int		num_of_directories;
	(void)str;

	env_path_index = env_value_exists(env, "PATH");
	if (env_path_index == -1)
		return ("");
	path_var = env[env_path_index];
	i = 0;
	num_of_directories = count_directories(path_var);
	while (i < num_of_directories)
	{
		directory_path = get_directory_by_number(path_var, i);
		if (check_if_file_exists(str, directory_path) == 1)
			return (directory_path);
		i++;
	}
	return ("/bin/");
}
