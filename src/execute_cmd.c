/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalbers <jalbers@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/20 14:40:05 by jalbers           #+#    #+#             */
/*   Updated: 2023/07/26 16:46:19 by jalbers          ###   ########.fr       */
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

char	*add_exec_path(char *str, char **env)
{
	int		i;
	int		size;
	char	*pwd;

	i = 0;
	while (env[i])
	{
		size = 0;
		while (env[i][size] != '=')
			size++;
		if (!ft_strncmp("PWD", env[i], 3) && size == 3)
			pwd = ft_strdup(env[i] + size + 1);
		i++;
	}
	printf("%s\n", ft_strjoin(pwd, str + 1));
	return (ft_strjoin(pwd, str + 1));
}

int	execute_using_execve(t_process *process, char **str, char **env)
{
	char	*cmd_path;
	pid_t	pid;
	(void)process;

	if (str[0][0] == '.' && str[0][1] == '/')
		cmd_path = add_exec_path(str[0], env);
	else
		cmd_path = add_path_prefix(str[0]);
	pid = fork();
	if (pid == 0)
	{
		execve(cmd_path, str, NULL);
		perror("execvp");
		exit(0);
	}
	else if (pid > 0)
	{
	/* 	wait(NULL); */
		int	status;
		waitpid(pid, &status, 0);
	}
	else
		perror("fork");
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
		execute_using_execve(process, args, shell->env);
	return (0);
}
