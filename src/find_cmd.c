/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chustei <chustei@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/10 18:04:21 by chustei           #+#    #+#             */
/*   Updated: 2023/07/11 13:26:12 by chustei          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	process_command_token(t_token **tokens, t_token **cur_token,
	t_token **prev_token, t_group *new_group)
{
	new_group->cmd = ft_strdup((*cur_token)->value);

	if (*prev_token != NULL)
	{
		update_prev_token_next(prev_token, cur_token);
	}
	else
	{
		update_tokens_head(tokens, cur_token);
	}

	if (*cur_token != NULL && (*cur_token)->type == T_SPACE)
	{
		if (*prev_token != NULL)
		{
			update_prev_token_next(prev_token, cur_token);
		}
		else
		{
			update_tokens_head(tokens, cur_token);
		}
	}
}

void	find_cmd(t_token **tokens, t_group *new_group)
{
	t_token	*cur_token;
	t_token	*prev_token;

	cur_token = *tokens;
	prev_token = NULL;
	while (cur_token != NULL && cur_token->type != T_PIPE)
	{
		if (is_redirection(cur_token))
			skip_redirection(&cur_token);
		else if (is_valid_word_token(cur_token)
			&& !starts_with_dollar(cur_token))
		{
			process_command_token(tokens, &cur_token, &prev_token, new_group);
			break ;
		}
		prev_token = cur_token;
		cur_token = cur_token->next;
	}
}
