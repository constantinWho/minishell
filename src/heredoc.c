/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalbers <jalbers@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/21 13:48:02 by josephalber       #+#    #+#             */
/*   Updated: 2023/07/26 13:17:05 by jalbers          ###   ########.fr       */
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

int	heredoc(t_redir *redir, t_minishell *shell)
{
	char	*input;
	int		fd;

	fd = open("tmp_file", O_RDWR | O_CREAT | O_TRUNC, 0777);
	shell->tmp_file_created = 1;
	while (1)
	{
		input = readline("heredoc> ");
		if (str_match_new(input, redir->arg) == 1)
			break ;
		write(fd, input, str_len(input));
		write(fd, "\n", 1);
		free(input);
	}
	free(input);
	return (fd);
}
