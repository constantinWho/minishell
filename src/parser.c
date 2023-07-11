/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chustei <chustei@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/10 18:12:42 by chustei           #+#    #+#             */
/*   Updated: 2023/07/11 17:25:42 by chustei          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

/*

void	parser(t_minishell *shell)
{
	print_linked_list(shell->tokens);
	find_cmd(&shell->tokens);
	print_linked_list(shell->tokens);
}
 */

int	ft_tokens_size(t_token *lst)
{
	size_t	i;

	i = 0;
	while (lst != NULL)
	{
		lst = lst->next;
		i++;
	}
	return (i);
}

void	print_linked_list(t_token *head)
{
	t_token	*current;

	current = head;
	while (current != NULL)
	{
		printf("TYPE[%i]: %s\n", current->type, current->value);
		current = current->next;
	}
}

int	print_size(t_group *lst)
{
	size_t	i;

	i = 0;
	while (lst != NULL)
	{
		lst = lst->next;
		i++;
	}
	return (i);
}

t_group	*create_group(void)
{
	t_group	*new_group;

	new_group = (t_group *)malloc(sizeof(t_group));
	new_group->cmd = NULL;
	new_group->args = NULL;
	new_group->redirs = NULL;
	new_group->next = NULL;
	return (new_group);
}

/* void find_redirs()
{
	find_redir();
	find_arg();
} */

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
void	add_group_to_struct(t_group **groups, t_group *new_group)
{
	t_group	*cur;

	if (new_group != NULL)
	{
		if (*groups == NULL)
			*groups = new_group;
		else
		{
			cur = *groups;
			while (cur->next != NULL)
				cur = cur->next;
			cur->next = new_group;
		}
	}
}

/* void	add_group(t_token *tokens, t_group **groups)
{
	t_group	*new_group;

	if (check_if_first_pipe(tokens))
		return ;
	new_group = create_group();
	find_cmd(&tokens, new_group);
	add_group_to_struct(groups, new_group);
	// Access the first group using *groups
	printf("size: %s\n", (*groups)->cmd);
} */

void add_group(t_token *tokens, t_group **groups)
{
	t_group	*new_group;

	if (!check_if_first_pipe(tokens))
		return ;
	new_group = create_group();
	print_linked_list(tokens);
	find_cmd(&tokens, new_group);
	find_args(&tokens, new_group);
	add_group_to_struct(groups, new_group);
	int i = 0;
	while (new_group->args[i])
	{
		printf("ARG[%i]: %s\n", i, new_group->args[i]);
		i++;
	}
	i = 0;
	printf("TOKENS SIZE: %i \n", ft_tokens_size(tokens));
	print_linked_list(tokens);
}

/*	find_cmd();
	find_args();
	find_redirs(); */

void	parser(t_minishell *shell)
{
	t_token	*tokens;
	t_group	*groups;

	tokens = shell->tokens;
	groups = shell->groups;
	if (!tokens)
		return ;
	add_group(tokens, &groups);
}
