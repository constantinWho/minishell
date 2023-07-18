/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_group_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chustei <chustei@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/18 16:46:14 by chustei           #+#    #+#             */
/*   Updated: 2023/07/18 16:53:51 by chustei          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	check_if_first_pipe(t_token *tokens)
{
	t_token	*current;

	current = tokens;
	if (current->type == T_PIPE)
	{
		printf("bash: syntax error near unexpected token `|'\n");
		return (0);
	}
	return (1);
}

void	delete_first_space_if_exists(t_token **head)
{
	t_token	*cur_token;

	cur_token = *head;
	if (cur_token != NULL)
	{
		if (cur_token->type == T_SPACE)
		{
			if (cur_token->next)
				*head = cur_token->next;
			else
				*head = NULL;
			free(cur_token->value);
			free(cur_token);
		}
	}
}

void	delete_pipe_if_exists(t_token **head)
{
	t_token	*cur_token;

	cur_token = *head;
	if (cur_token != NULL)
	{
		if (cur_token->type == T_PIPE)
		{
			if (cur_token->next)
				*head = cur_token->next;
			else
				*head = NULL;
			free(cur_token->value);
			free(cur_token);
		}
	}
}
