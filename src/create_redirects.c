/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_redirects.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: josephalbers <josephalbers@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/20 14:31:29 by jalbers           #+#    #+#             */
/*   Updated: 2023/08/03 15:20:21 by josephalber      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	create_redirect_files(t_group *group, t_redir *redir, t_minishell *shell)
{
	int		fd_out;
	int		fd_in;

	fd_out = -1;
	fd_in = -1;
	while (redir != NULL)
	{
		if (str_match(">", redir->redir) == 1)
			fd_out = open(redir->arg, O_WRONLY | O_CREAT | O_TRUNC, 0777);
		else if (str_match(">>", redir->redir) == 1)
			fd_out = open(redir->arg, O_WRONLY | O_CREAT | O_APPEND, 0777);
		else if (str_match("<", redir->redir) == 1)
			fd_in = open(redir->arg, O_RDONLY);
		else if (str_match("<<", redir->redir) == 1)
		{
			heredoc(redir->arg, shell, "heredoc> ", 1);
			fd_in = open("tmp_file1", O_RDONLY);
		}
		redir = redir->next;
	}
	group->redirect_fd_in = fd_in;
	group->redirect_fd_out = fd_out;
	return (0);
}

int	set_up_redirects_for_groups(t_group *group, t_minishell *shell)
{
	t_group	*current_group;

	current_group = group;
	while (current_group)
	{
		create_redirect_files(current_group, current_group->redirs, shell);
		current_group = current_group->next;
	}
	return (0);
}
