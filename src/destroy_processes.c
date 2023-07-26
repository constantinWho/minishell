/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destroy_processes.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalbers <jalbers@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/26 12:50:23 by jalbers           #+#    #+#             */
/*   Updated: 2023/07/26 13:01:14 by jalbers          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	destroy_processes(t_process *process, t_minishell *shell)
{
	if (process->index != process->pipe_total)
	{
		free(process);
		exit(0);
	}
	free(process);
	if (shell->tmp_file_created == 1)
	{
		remove_file("tmp_file");
		shell->tmp_file_created = 0;
	}
	return (0);
}