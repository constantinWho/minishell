/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalbers <jalbers@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/20 14:40:05 by jalbers           #+#    #+#             */
/*   Updated: 2023/08/04 14:46:23 by jalbers          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

char	*add_path(char *str, char **env)
{
	char	*dir_path;
	char	*new_str;
	int		i;
	int		j;

	dir_path = get_correct_directory(str, env);
	new_str = malloc((str_len(dir_path) + str_len(str) + 1) * sizeof(char));
	i = 0;
	j = 0;
	while (dir_path[i])
		new_str[j++] = dir_path[i++];
	i = 0;
	while (str[i])
		new_str[j++] = str[i++];
	new_str[j] = '\0';
	if (dir_path[0])
		free(dir_path);
	return (new_str);
}

char	*add_exec_path(char *str, char **env)
{
	int		i;
	int		size;
	char	*pwd;
	char	*path;

	i = 0;
	path = NULL;
	while (env[i])
	{
		size = 0;
		while (env[i][size] != '=')
			size++;
		if (!ft_strncmp("PWD", env[i], 3) && size == 3)
			pwd = ft_strdup(env[i] + size + 1);
		i++;
	}
	path = ft_strjoin(pwd, str + 1);
	free(pwd);
	return (path);
}

int	get_exit_status_of_execve(int pid)
{
	int		exit_status_int;

	waitpid(pid, &exit_status_int, 0);
	exit_status_int = exit_status_int >> 8;
	return (exit_status_int);
}

int	execute_using_execve(char **str, t_minishell *shell)
{
	char	*cmd_path;
	pid_t	pid;
	int		exit_status;

	if (str[0][0] == '.' && str[0][1] == '/')
		cmd_path = add_exec_path(str[0], shell->env);
	else
		cmd_path = add_path(str[0], shell->env);
	pid = fork();
	if (pid == 0)
	{
		execve(cmd_path, str, NULL);
		perror("execvp");
		exit(1);
	}
	else if (pid > 0)
		exit_status = get_exit_status_of_execve(pid);
	else
	{
		perror("fork");
		return (1);
	}
	free (cmd_path);
	return (exit_status);
}

int	execute_cmd_with_args(t_minishell *shell, char **args)
{
	int		exit_status_int;
	char	*exit_status_str;

	if (str_match(args[0], "env") == 1)
		exit_status_int = ft_env(shell);
	else if (str_match(args[0], "echo") == 1)
		exit_status_int = ft_echo(args);
	else if (str_match(args[0], "export") == 1)
		exit_status_int = ft_export(args, shell);
	else if (str_match(args[0], "unset") == 1)
		exit_status_int = ft_unset(args, shell);
	else if (str_match(args[0], "cd") == 1)
		exit_status_int = ft_cd(args, shell);
	else if (str_match(args[0], "pwd") == 1)
		exit_status_int = ft_pwd();
	else
		exit_status_int = execute_using_execve(args, shell);
	exit_status_str = ft_itoa(exit_status_int);
	if (env_value_exists(shell->env, "EXIT_STATUS") != -1)
		change_env(shell->env, "EXIT_STATUS", exit_status_str);
	else
		shell->env = add_env_value(shell->env, "EXIT_STATUS", exit_status_str);
	free(exit_status_str);
	return (0);
}
