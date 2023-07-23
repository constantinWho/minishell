/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chustei <chustei@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/21 13:48:02 by josephalber       #+#    #+#             */
/*   Updated: 2023/07/23 14:23:51 by chustei          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	heredoc(t_redir *redir, t_process *process, t_minishell *shell)
{
	char	*input;
	char	*full_input;

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
	printf("%s\n", full_input);
	dup2(process->fd_write, 1);
	// write(process->fd_write, "wagwan", 6);
	free(input);
	return (0);
}
