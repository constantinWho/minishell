/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_process.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalbers <jalbers@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/03 15:20:58 by jalbers           #+#    #+#             */
/*   Updated: 2023/07/20 19:14:07 by jalbers          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

// int attach_pipe_input_to_args(t_minishell *shell, t_process *process)
// {
// 	int	i;

// 	int	file;
// 	if (process->pipe_input != NULL)
// 	{
// 		file = open("example.txt", O_WRONLY | O_CREAT, 0644);
// 		write(file, process->pipe_input, strlen(process->pipe_input));
// 	}

// 	i = 0;
// 	while (shell->args[i])
// 		i++;
// 	// shell->args[i++] = process->pipe_input;
// 	shell->args[i++] = "example.txt";
// 	shell->args[i] = NULL;
// 	return (file);
// }

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

void	insert_str(char *dest, char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		dest[i] = str[i];
		i++;
	}
	dest[i] = '\0';
}

int	calc_array_len(char **array)
{
	int	i;

	i = 0;
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

	array_len = calc_array_len(args);
	cmd_and_args = malloc((array_len + 2) * sizeof(char *));
	i = 0;
	while (i < array_len + 1)
	{
		if (i == 0)
			str = cmd;
		else
			str = args[i - 1];
		cmd_and_args[i] = malloc((str_len(str) + 1) * sizeof(char));
		insert_str(cmd_and_args[i], str);
		i++;
	}
	cmd_and_args[i] = NULL;
	return (cmd_and_args);
}

int	execute_process(t_minishell *shell, t_process *process)
{
	t_group	*correct_group;
	char	**cmd_and_args;

	correct_group = get_correct_group(shell, process->index);
	if (correct_group != NULL && correct_group->redirs != NULL)
		create_redirect_files(correct_group->redirs, process);
	if (correct_group != NULL && correct_group->cmd != NULL)
	{
		cmd_and_args = join_cmd_and_args(correct_group->cmd,
				correct_group->args);
		execute_cmd_with_args(shell, process, cmd_and_args);
		free_array(cmd_and_args);
	}
	return (0);
}
