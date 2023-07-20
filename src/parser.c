/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalbers <jalbers@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/10 18:12:42 by chustei           #+#    #+#             */
/*   Updated: 2023/07/20 19:28:50 by jalbers          ###   ########.fr       */
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
		int i = 0;
		while (current->args[i])
		{
			printf("ARG[%i]: %s\n", i, current->args[i]);
			i++;
		}
		current = current->next;
	}
}

void	parser(t_minishell *shell)
{
	t_token	*tokens;
	t_group	*groups;

	tokens = shell->tokens;
	groups = NULL;
	if (!tokens)
		return ;
	add_group(tokens, &groups, shell->env);
	shell->groups = groups;
	print_group(shell->groups);
}
