/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chustei <chustei@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/10 18:12:42 by chustei           #+#    #+#             */
/*   Updated: 2023/07/18 19:12:21 by chustei          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	print_group(t_group *head)
{
	t_group	*current;

	current = head;
	while (current != NULL)
	{
		printf("CMD: %s\n", current->cmd);
		current = current->next;
	}
}

void	parser(t_minishell *shell)
{
	t_token	*tokens;
	t_group	*groups;

	tokens = shell->tokens;
	groups = shell->groups;
	if (!tokens)
		return ;
	add_group(tokens, &groups);
	shell->groups = groups;
	print_group(shell->groups);
}
