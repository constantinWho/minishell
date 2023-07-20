/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalbers <jalbers@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/20 14:40:05 by jalbers           #+#    #+#             */
/*   Updated: 2023/07/20 17:01:34 by jalbers          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

char	*add_path_prefix(char *str)
{
	char	*prefix;
	char	*new_str;
	int		i;
	int		j;

	prefix = "/bin/";
	new_str = malloc((5 + str_len(str) + 1) * sizeof(char));
	i = 0;
	j = 0;
	while (prefix[i])
		new_str[j++] = prefix[i++];
	i = 0;
	while (str[i])
		new_str[j++] = str[i++];
	new_str[j] = '\0';
	return (new_str);	
}


int execute_using_execve(t_process *process, char **str)
{
	char	*cmd_path;
	
	cmd_path = add_path_prefix(str[0]);

	pid_t pid = fork();
	if (pid == 0) {
		dup2(process->fd_read, 0);
		execve(cmd_path, str, NULL);
		perror("execvp");
		close(process->fd_read);
	} else if (pid > 0) {
		wait(NULL);
	} else {
		perror("fork");
	}
	free (cmd_path);
	return (0);
}

int execute_cmd_with_args(t_minishell *shell, t_process *process, char **args)
{

	if (str_match(args[0], "env") == 1)
		ft_env(shell);
	else if (str_match(args[0], "echo") == 1)
	 	ft_echo(args);
	else if (str_match(args[0], "export") == 1)
		ft_export(args, shell);
	else if (str_match(args[0], "unset") == 1)
		ft_unset(args, shell);
	else if (str_match(args[0], "cd") == 1)
		ft_cd(args, shell);
	else if (str_match(args[0], "pwd") == 1)
		ft_pwd();
	else
		execute_using_execve(process, args);
	return (0);
}
