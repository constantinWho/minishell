/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chustei <chustei@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/10 18:12:42 by chustei           #+#    #+#             */
/*   Updated: 2023/07/17 19:21:49 by chustei          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

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
		printf("TYPE[%i]: {%s}; ", current->type, current->value);
		current = current->next;
	}
	printf("\n");
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

void add_group(t_token *tokens, t_group **groups)
{
	t_group	*new_group;

	delete_first_space_if_exists(&tokens);
	if (!check_if_first_pipe(tokens))
		return ;
	new_group = create_group();
	print_linked_list(tokens);
	find_cmd(&tokens, new_group);
	find_args(&tokens, new_group);
	printf("TOKENS SIZE: %i \n", ft_tokens_size(tokens));
	find_redirs(&tokens, new_group);
	delete_pipe_if_exists(&tokens);
	add_group_to_struct(groups, new_group);
	printf("CMD: %s\n", new_group->cmd);
	int i = 0;
	while (new_group->args[i])
	{
		printf("ARG[%i]: {%s}; ", i, new_group->args[i]);
		i++;
	}
	printf("\n");
	i = 0;
	printf("TOKENS SIZE: %i \n", ft_tokens_size(tokens));
	print_redir(new_group->redirs);
	print_linked_list(tokens);
	if (ft_tokens_size(tokens) > 0)
		add_group(tokens, groups);
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
}
