/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chustei <chustei@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 13:20:00 by chustei           #+#    #+#             */
/*   Updated: 2023/07/20 12:11:46 by chustei          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	skip_redirection(t_token **cur_token)
{
	if ((*cur_token)->next != NULL)
	{
		*cur_token = (*cur_token)->next;
		if ((*cur_token)->type == T_SPACE && (*cur_token)->next != NULL)
			*cur_token = (*cur_token)->next;
	}
}

int	is_redirection(t_token *token)
{
	return (token->type == T_REDIR_IN || token->type == T_REDIR_OUT
		|| token->type == T_REDIR_OUT_APPEND || token->type == T_HEREDOC);
}

int	is_valid_word_token(t_token *token)
{
	return (token->type == T_1Q_WORD || token->type == T_2Q_WORD
		|| token->type == T_WORD);
}

int	starts_with_dollar(t_token *token)
{
	return (token->value[0] == '$');
}

void	skip_redir_block(t_token **cur_token)
{
	*cur_token = (*cur_token)->next;
	if (*cur_token != NULL && (*cur_token)->type == T_SPACE)
	{
		*cur_token = (*cur_token)->next;
		if (*cur_token != NULL && is_valid_word_token(*cur_token))
		{
			*cur_token = (*cur_token)->next;
			if (*cur_token != NULL && (*cur_token)->type == T_SPACE)
				*cur_token = (*cur_token)->next;
		}
	}
	else if (*cur_token != NULL && is_valid_word_token(*cur_token))
	{
		*cur_token = (*cur_token)->next;
		if (*cur_token != NULL && (*cur_token)->type == T_SPACE)
			*cur_token = (*cur_token)->next;
	}
}
