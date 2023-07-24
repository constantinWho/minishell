/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalbers <jalbers@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/21 13:48:02 by josephalber       #+#    #+#             */
/*   Updated: 2023/07/24 17:55:48 by jalbers          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	heredoc(t_redir *redir, t_process *process, t_minishell *shell)
{
	char	*input;
	char	*full_input;
	int		fd;
	// (void)process;
	// (void)redir;
	// (void)shell;

	fd = open("tmp_file", O_WRONLY | O_CREAT | O_TRUNC, 0777);
	full_input = malloc(1);
	full_input[0] = '\0';
	dup2(shell->original_stdout, 1);
	while (1)
	{
		input = ft_readline("heredoc> ");
		if (str_match(input, redir->arg) == 1)
			break ;
		full_input = ft_strjoin(full_input, input);
		free(input);
	}
	
	// dup2(fd, 1);
	// printf("asd");
	
	write(fd, "HELLO", 5);
	
	close(fd);
	dup2(process->fd_write, 1);
	free(full_input);
	free(input);
	return (fd);
}
