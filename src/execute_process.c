/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_process.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chustei <chustei@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/03 15:20:58 by jalbers           #+#    #+#             */
/*   Updated: 2023/07/26 16:28:11 by chustei          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

t_group	*get_correct_group(t_minishell *shell, int process_index)
{
	int		i;

	i = 0;
	while (i < process_index)
	{
		shell->groups = shell->groups->next;
		i++;
	}
	return (shell->groups);
}

int	calc_array_len(char **array)
{
	int	i;

	i = 0;
	if (!array)
		return (0);
	while (array[i] != NULL)
		i++;
	return (i);
}

char	**join_cmd_and_args(char *cmd, char **args)
{
	char	**cmd_and_args;
	int		array_len;
	int		i;
	char	*str;

	array_len = 0;
	if (args)
		array_len = calc_array_len(args);
	cmd_and_args = malloc((array_len + 2) * sizeof(char *));
	i = 0;
	while (i < array_len + 1)
	{
		if (i == 0)
			str = ft_strdup(cmd);
		else
			str = ft_strdup(args[i - 1]);
		cmd_and_args[i] = ft_strdup(str);
		i++;
	}
	cmd_and_args[i] = NULL;
	return (cmd_and_args);
}

void	set_stdin_stdout(t_process *process, t_group *correct_group)
{
	if (correct_group->redirect_fd_in != -1)
		dup2(correct_group->redirect_fd_in, 0);
	else
		dup2(process->fd_read, 0);
	if (correct_group->redirect_fd_out != -1)
		dup2(correct_group->redirect_fd_out, 1);
	else
		dup2(process->fd_write, 1);
}

int	execute_process(t_minishell *shell, t_process *process)
{
	t_group	*correct_group;
	char	**cmd_and_args;

	correct_group = get_correct_group(shell, process->index);
	if (correct_group == NULL || correct_group->cmd == NULL)
		return (1);
	set_stdin_stdout(process, correct_group);
	cmd_and_args = join_cmd_and_args(correct_group->cmd,
			correct_group->args);
	execute_cmd_with_args(shell, process, cmd_and_args);
	free_array(cmd_and_args);
	return (0);
}
