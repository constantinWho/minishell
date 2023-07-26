/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_group.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalbers <jalbers@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/18 16:46:14 by chustei           #+#    #+#             */
/*   Updated: 2023/07/26 12:25:40 by jalbers          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

t_group	*create_group(void)
{
	t_group	*new_group;

	new_group = (t_group *)malloc(sizeof(t_group));
	new_group->cmd = NULL;
	new_group->args = NULL;
	new_group->redirs = NULL;
	new_group->redirect_fd_in = -1;
	new_group->redirect_fd_out = -1;
	new_group->next = NULL;
	return (new_group);
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

void	add_group(t_token *tokens, t_group **groups, char **env)
{
	t_group	*new_group;

	delete_first_space_if_exists(&tokens);
	if (!check_if_first_pipe(tokens))
		return ;
	new_group = create_group();
	find_cmd(&tokens, new_group);
	find_args(&tokens, new_group, env);
	find_redirs(&tokens, new_group);
	delete_pipe_if_exists(&tokens);
	add_group_to_struct(groups, new_group);
	if (ft_tokens_size(tokens) > 0)
		add_group(tokens, groups, env);
}

/*
void	print_redir(t_redir *head)
{
	t_redir	*current;

	current = head;
	while (current != NULL)
	{
		printf("%s : %s\n", current->redir, current->arg);
		current = current->next;
	}
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
 */
