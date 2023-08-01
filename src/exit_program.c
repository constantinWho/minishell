/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_program.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chustei <chustei@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/27 15:19:13 by jalbers           #+#    #+#             */
/*   Updated: 2023/08/01 18:12:09 by chustei          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

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

int	free_data(t_minishell *shell, char *input)
{
	free(input);
	free_groups(shell->groups);
	free_args(shell->args);
	return (0);
}

int	exit_program(t_minishell *shell, char *input)
{
	close(shell->original_stdout);
	close(shell->original_stdin);
	free (input);
	free_array(shell->env);
	free(shell);
	return (0);
}
