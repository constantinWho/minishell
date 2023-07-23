/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_redirects.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chustei <chustei@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/20 14:31:29 by jalbers           #+#    #+#             */
/*   Updated: 2023/07/23 14:22:54 by chustei          ###   ########.fr       */
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

int	check_if_file_exists(char *dir_path, char *file_name)
{
	DIR *dir;
	struct dirent *entry;

	if (dir_path[0])
		dir = opendir(dir_path);
	else
		dir = opendir(".");
	if (dir == NULL) {
		perror("opendir");
		return 2;
	}
	while ((entry = readdir(dir)) != NULL)
	{
		if (str_match(entry->d_name, file_name) == 1)
		{
			closedir(dir);
			return (1);
		}
		// printf("%s\n", entry->d_name);
	}
	closedir(dir);
	return 0;
}

int	create_redirect_files(t_redir *redir, t_process *process, t_minishell *shell)
{
	int		fd;
	int		dup_fd;

	dup_fd = 1;
	while (redir != NULL)
	{
		if (str_match(">", redir->redir) == 1)
			fd = open(redir->arg, O_WRONLY | O_CREAT | O_TRUNC, 0777);
		else if (str_match(">>", redir->redir) == 1)
			fd = open(redir->arg, O_WRONLY | O_CREAT | O_APPEND, 0777);
		else if (str_match("<", redir->redir) == 1)
		{
			fd = open(redir->arg, O_RDONLY);
			if (process->index == 0)
				dup_fd = 0;
			else
				dup_fd = process->fd_read;
		}
		else if (str_match("<<", redir->redir) == 1)
		{
			heredoc(redir, process, shell);
			redir = redir->next;
			return (0);
		}
		if (dup2(fd, dup_fd) == -1)
		{
			printf("Failed to duplicate file descriptor\n");
			close(fd);
			return (1);
		}
		close(fd);
		redir = redir->next;
	}
	return (0);
}
