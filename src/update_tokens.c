/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_tokens.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chustei <chustei@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 13:21:47 by chustei           #+#    #+#             */
/*   Updated: 2023/07/18 16:43:55 by chustei          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	update_prev_token_next(t_token **prev_token, t_token **cur_token)
{
	(*prev_token)->next = (*cur_token)->next;
	free((*cur_token)->value);
	free(*cur_token);
	*cur_token = (*prev_token)->next;
}

void	update_tokens_head(t_token **tokens, t_token **cur_token)
{
	*tokens = (*cur_token)->next;
	free((*cur_token)->value);
	free(*cur_token);
	*cur_token = *tokens;
}


void	skip_redir_block_update_prev_token(t_token **cur_token,
	t_token **prev_token)
{
	*cur_token = (*cur_token)->next;
	if (*cur_token != NULL && (*cur_token)->type == T_SPACE)
	{
		*cur_token = (*cur_token)->next;
		if (*cur_token != NULL && is_valid_word_token(*cur_token))
		{
			*cur_token = (*cur_token)->next;
			if (*cur_token != NULL && (*cur_token)->type == T_SPACE)
			{
				*prev_token = *cur_token;
				*cur_token = (*cur_token)->next;
			}
		}
	}
	else if (*cur_token != NULL && is_valid_word_token(*cur_token))
	{
		*cur_token = (*cur_token)->next;
		if (*cur_token != NULL && (*cur_token)->type == T_SPACE)
		{
			*prev_token = *cur_token;
			*cur_token = (*cur_token)->next;
		}
	}
}
