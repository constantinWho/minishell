/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalbers <jalbers@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/07 12:03:02 by chustei           #+#    #+#             */
/*   Updated: 2023/07/20 17:10:08 by jalbers          ###   ########.fr       */
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
	shell->original_stdin= dup(1);
	return (shell);
}

// 1. Exits the minishell on CTRL-D
// 2. Add the input to the command history
char	*ft_readline(void)
{
	char	*input;

	input = readline("Minishell > ");
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

/* void	create_group(t_minishell *shell, char *type, char *value)
{
	t_group	*new_group;
	t_group	*curr_group;

	new_group = (t_group *)malloc(sizeof(t_group));
	new_group->type = ft_strdup(type);
	new_group->value = ft_strdup(value);
	new_group->children = NULL;
	new_group->num_children = 0;
	new_group->next = NULL;

	// Add the current group to the tree
	if (shell->groups == NULL)
		shell->groups = new_group;
	else
	{
		curr_group = shell->groups;
		while (curr_group->next != NULL)
			curr_group = curr_group->next;
		curr_group->next = new_group;
	}
} */

/* void	ft_parser(t_minishell *shell)
{
	t_token	*curr_token;

	curr_token = shell->tokens;
	while (curr_token != NULL)
	{
		if (ft_check_cmd(curr_token->str))
		{
			create_group(shell, "CMD", curr_token->str);
			printf("+++++++++ Type: %s\n", shell->groups->type);
			printf("+++++++++ Value: %s\n", shell->groups->value);
		}
		else if (ft_strncmp(curr_token->type, "word", 3))
			append_children();
		printf("--------- Type: %s\n", curr_token->type);
		curr_token = curr_token->next;
	}
}
 */

/* void	ft_parser(t_minishell *shell)
{
	t_token	*current_t;
	t_group	*current_g;

	current_g = (t_group *)malloc(sizeof(t_group));
	current_g = shell->tree;
	current_t = shell->tokens;
	if (ft_check_cmd(current_t->str))
	{
		current_g->type = ft_strdup("CMD");
		current_g->value = ft_strdup(current_t->str);
		printf("+++++++++ %s\n", current_g->type);
		printf("+++++++++ %s\n", current_g->value);
	}
	else
		return ;
} */


int	count_pipes(char *input_str)
{
	int	pipe_count;
	int	i;

	pipe_count = 0;
	i = 0;
	while (input_str[i])
	{
		if (input_str[i] == '|')
			pipe_count++;
		i++;
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
		input = ft_readline();
		ft_lexer(shell, input);
		parser(shell);
		process = create_processes(input, count_pipes(input));
		// process->pipe_input = read_input(process);
		create_redirect_files(shell->groups->redirs);
		execute_process(shell, process);
		free(input);
		free_groups(shell->groups);
		free_args(shell->args);
		destroy_processes(process);
		wait(NULL);

		// restore stdout and stdin
		dup2(shell->original_stdout, 1);
		dup2(shell->original_stdin, 0);

	
		// while (shell->groups != NULL)
		// {
			// printf("CMD:%s ", shell->groups->cmd);
			// int i = 0;
			// while (shell->groups->args[i])
			// {
				// printf("Arg%i:%s ", i, shell->groups->args[i]);
				// i++;
			// }
			// shell->groups = shell->groups->next;
			// printf("\n");
		// }



		//call_method(shell);
		//free_tokens(shell->tokens);
	}
    close(shell->original_stdout);
    close(shell->original_stdin);
	free (input);
	free_array(shell->env);
	free(shell);
	return (0);
}
