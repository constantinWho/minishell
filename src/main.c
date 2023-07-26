/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalbers <jalbers@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/07 12:03:02 by chustei           #+#    #+#             */
/*   Updated: 2023/07/26 16:46:43 by jalbers          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

t_minishell	*create_struct(char **env)
{
	t_minishell	*shell;

	shell = (t_minishell *)malloc(sizeof(t_minishell));
	shell->tokens = NULL;
	shell->env = copy_realloc_data(env, 0);
	shell->original_stdout = dup(1);
	shell->original_stdin= dup(0);
	return (shell);
}

// 1. Exits the minishell on CTRL-D
// 2. Add the input to the command history
char	*ft_readline(char *prompt)
{
	char	*input;

	input = readline(prompt);
	if (input == NULL)
		exit(EXIT_SUCCESS);
	if (input)
		add_history(input);
	return (input);
}

// Calling the Methods
void	call_method(t_minishell *shell)
{
	if (fork() == 0)
	{
		execvp(shell->args[0], shell->args);
		perror("Command execution failed");
		exit(EXIT_FAILURE);
	}
	else
		wait(NULL);
}

int	ft_check_cmd(char *str)
{
	if (ft_strncmp(str, "cd", 2) == 0)
		return (1);
	else if (ft_strncmp(str, "echo", 4) == 0)
		return (1);
	else if (ft_strncmp(str, "pwd", 3) == 0)
		return (1);
	else if (ft_strncmp(str, "export", 6) == 0)
		return (1);
	else if (ft_strncmp(str, "unset", 5) == 0)
		return (1);
	else if (ft_strncmp(str, "env", 3) == 0)
		return (1);
	else if (ft_strncmp(str, "exit", 4) == 0)
		return (1);
	else
		return (0);
}

int	count_pipes(t_group *group)
{
	int	pipe_count;

	pipe_count = 0;
	while (group)
	{
		pipe_count++;
		group = group->next;
	}
	return (pipe_count);
}

void	free_redirs(t_redir *head)
{
	t_redir	*current;
	t_redir	*next;

	current = head;
	while (current != NULL)
	{
		free(current->redir);
		free(current->arg);
		next = current->next;
		free(current);
		current = next;
	}
}

void	free_groups(t_group *head)
{
	t_group	*current;
	t_group	*next;
	int		i;

	current = head;
	while (current != NULL)
	{
		free(current->cmd);
		i = 0;
		while (current->args[i])
		{
			free(current->args[i]);
			i++;
		}
		free(current->args);
		free_redirs(current->redirs);
		next = current->next;
		free(current);
		current = next;
	}
}

void	free_args(char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
	i++;
}

int	main(int ac, char **av, char **env)
{
	char		*input;
	t_minishell	*shell;
	t_process	*process;

	(void)ac;
	(void)av;
	shell = create_struct(env);
	ignore_signal_for_shell();
	while (1)
	{
		input = ft_readline("Minishell > ");
		ft_lexer(shell, input);
		if (!shell->tokens)
			continue ;
		parser(shell);
		set_up_redirects_for_groups(shell->groups, shell);
		process = create_processes(count_pipes(shell->groups));
		execute_process(shell, process);
		free(input);
		free_groups(shell->groups);
		free_args(shell->args);
		destroy_processes(process, shell);
		wait(NULL);
		dup2(shell->original_stdout, 1);
		dup2(shell->original_stdin, 0);
	}
    close(shell->original_stdout);
    close(shell->original_stdin);
	free (input);
	free_array(shell->env);
	free(shell);
	return (0);
}
