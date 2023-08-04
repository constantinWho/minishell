/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalbers <jalbers@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/21 13:48:02 by josephalber       #+#    #+#             */
/*   Updated: 2023/08/04 14:00:47 by jalbers          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	remove_file(char *file_name)
{
	char	*args[3];
	int		pid;

	args[0] = "rm";
	args[1] = file_name;
	args[2] = NULL;
	pid = fork();
	if (pid == 0)
	{
		execve("/bin/rm", args, NULL);
		perror("execvp");
	}
	else if (pid > 0)
		wait(NULL);
	else
		perror("fork");
	return (0);
}

int	str_match_new(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1[i] || s2[i])
	{
		if (s1[i] != s2[i])
			return (0);
		i++;
	}
	return (1);
}

char	*generate_file_name(char *name, int id)
{
	char	*id_str;
	char	*final_file_name;

	id_str = ft_itoa(id);
	final_file_name = ft_strjoin(name, id_str);
	return (final_file_name);
}

int	heredoc(char *end_signal, t_minishell *shell, char *label, int id)
{
	char	*tmp_file_name;
	char	*input;
	int		fd;

	tmp_file_name = generate_file_name("tmp_file", id);
	fd = open(tmp_file_name, O_RDWR | O_CREAT | O_TRUNC, 0777);
	shell->tmp_file_created = 1;
	while (1)
	{
		input = readline(label);
		if (input == NULL)
			exit(EXIT_SUCCESS);
		if (str_match_new(input, end_signal) == 1)
			break ;
		write(fd, input, str_len(input));
		write(fd, "\n", 1);
		free(input);
	}
	free(tmp_file_name);
	free(input);
	return (fd);
}
