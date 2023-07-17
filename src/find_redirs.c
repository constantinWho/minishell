/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_redirs.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chustei <chustei@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 18:36:30 by chustei           #+#    #+#             */
/*   Updated: 2023/07/17 11:24:48 by chustei          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

t_redir	*create_redir(char *str)
{
	t_redir	*new_redir;

	new_redir = (t_redir *)malloc(sizeof(t_redir));
	new_redir->redir = ft_strdup(str);
	new_redir->arg = NULL;
	new_redir->next = NULL;
	return (new_redir);
}

void	add_new_redir(t_redir **redirs, t_redir *new_redir)
{
	t_redir	*cur;

	if (new_redir != NULL)
	{
		if (*redirs == NULL)
			*redirs = new_redir;
		else
		{
			cur = *redirs;
			while (cur->next != NULL)
				cur = cur->next;
			cur->next = new_redir;
		}
	}
}

void	process_redir(t_token **cur_token, t_redir *new_redir)
{
	if (*cur_token != NULL && (*cur_token)->type == T_SPACE)
	{
		*cur_token = (*cur_token)->next;
		if (*cur_token != NULL && is_valid_word_token(*cur_token))
		{
			new_redir->arg = ft_strdup((*cur_token)->value);
			*cur_token = (*cur_token)->next;
		}
	}
	else if (*cur_token != NULL && is_valid_word_token(*cur_token))
	{
		new_redir->arg = ft_strdup((*cur_token)->value);
		*cur_token = (*cur_token)->next;
	}
}

void	find_redirs(t_token **tokens, t_group *new_group)
{
	t_token	*cur_token;
	t_token	*prev_token;
	t_redir	*new_redir;

	cur_token = *tokens;
	new_redir = NULL;
	prev_token = NULL;
	while (cur_token != NULL && cur_token->type != T_PIPE)
	{
		if (is_redirection(cur_token))
			new_redir = create_redir(cur_token->value);
		cur_token = cur_token->next;
		process_redir(&cur_token, new_redir);
		if (cur_token != NULL && cur_token->type == T_SPACE)
			cur_token = cur_token->next;
		add_new_redir(&new_group->redirs, new_redir);
	}
}
