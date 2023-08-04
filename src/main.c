/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: josephalbers <josephalbers@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/07 12:03:02 by chustei           #+#    #+#             */
/*   Updated: 2023/08/04 11:20:52 by josephalber      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

t_minishell	*create_struct(char **env)
{
	t_minishell	*shell;

	shell = (t_minishell *)malloc(sizeof(t_minishell));
	if (shell == NULL)
		exit(EXIT_FAILURE);
	shell->tokens = NULL;
	shell->env = copy_realloc_data(env, 0);
	shell->original_stdout = dup(1);
	shell->original_stdin = dup(0);
	shell->tmp_file_created = -1;
	shell->env = add_env_value(shell->env, "EXIT_STATUS", "0");
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

void	reset_stdin_stdout(t_minishell *shell)
{
	dup2(shell->original_stdout, 1);
	dup2(shell->original_stdin, 0);
}

int	count_pipes(t_group *group)
{
	int		pipe_count;
	t_group	*cur;

	pipe_count = 0;
	cur = group;
	while (cur)
	{
		pipe_count++;
		cur = cur->next;
	}
	return (pipe_count);
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
		{
			free(input);
			free_array(shell->args);
			continue ;
		}
		if (str_match(shell->tokens->value, "exit") == 1)
			break ;
		parser(shell);
		set_up_redirects_for_groups(shell->groups, shell);
		if (shell->groups)
		{
			process = create_processes(count_pipes(shell->groups));
			execute_process(shell, process);
			destroy_processes(process, shell);
		}
		wait(NULL);
		free_data(shell, input);
		reset_stdin_stdout(shell);
	}
	exit_program(shell, input);
	return (0);
}
