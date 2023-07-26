/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_redirects.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalbers <jalbers@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/20 14:31:29 by jalbers           #+#    #+#             */
/*   Updated: 2023/07/26 13:04:21 by jalbers          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	get_dir_len(char *full_path, int length)
{
	while (length != 0 && full_path[length] != '/')
		length--;
	return (length);
}

char	*get_dir_path(char *arg)
{
	char	*dir_path;
	int		full_path_len;
	int		dir_len;
	int		i;

	full_path_len = str_len(arg);
	dir_len = get_dir_len(arg, full_path_len);
	dir_path = malloc((dir_len + 1) * sizeof(char));
	i = 0;
	while (i < dir_len)
	{
		dir_path[i] = arg[i];
		i++;
	}
	dir_path[i] = '\0';
	return (dir_path);
}

char	*get_file_name(char *arg)
{
	char	*file_name;
	int		full_path_len;
	int		dir_len;
	int		i;

	full_path_len = str_len(arg);
	dir_len = get_dir_len(arg, full_path_len);
	if (dir_len != 0)
		dir_len++;
	file_name = malloc((full_path_len - dir_len) * sizeof(char));
	i = 0;
	while (i + dir_len < full_path_len)
	{
		file_name[i] = arg[i + dir_len];
		i++;
	}
	file_name[i] = '\0';
	return (file_name);
}

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
			heredoc(redir, shell);
			fd_in = open("tmp_file", O_RDONLY);
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
