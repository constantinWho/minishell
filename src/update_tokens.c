/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_tokens.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chustei <chustei@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 13:21:47 by chustei           #+#    #+#             */
/*   Updated: 2023/07/11 13:22:16 by chustei          ###   ########.fr       */
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
