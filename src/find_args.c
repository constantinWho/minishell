/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_args.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chustei <chustei@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 13:31:30 by chustei           #+#    #+#             */
/*   Updated: 2023/07/11 18:06:19 by chustei          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	count_args(t_token *tokens)
{
	t_token	*cur_token;
	int		count;

	cur_token = tokens;
	count = 0;
	while (cur_token != NULL && cur_token->type != T_PIPE)
	{
		if (is_redirection(cur_token))
		{
			cur_token = cur_token->next;
			if (cur_token != NULL && cur_token->type != T_PIPE
				&& is_valid_word_token(cur_token))
			{
				cur_token = cur_token->next;
				if (cur_token != NULL && cur_token->type != T_PIPE
					&& cur_token->type == T_SPACE)
					cur_token = cur_token->next;
			}
		}
		else if ((cur_token != NULL && cur_token->type != T_PIPE)
			&& (is_valid_word_token(cur_token)
				|| cur_token->type == T_SPACE))
			count++;
		if (cur_token != NULL)
			cur_token = cur_token->next;
	}
	return (count);
}

void	process_arg_token(t_token **tokens, t_token **cur_token,
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
}

void	find_args(t_token **tokens, t_group *new_group)
{
	t_token	*cur_token;
	t_token	*prev_token;
	int		args_num;
	int		i;

	cur_token = *tokens;
	prev_token = NULL;
	args_num = count_args(*tokens);
	new_group->args = (char **)malloc((args_num + 1) * sizeof(char *));
	printf("ARGS FOUND: %i\n", args_num);
	printf("CMD: %s\n", new_group->cmd);
	i = 0;
	while (cur_token != NULL && cur_token->type != T_PIPE)
	{
		if (is_redirection(cur_token))
		{
			cur_token = cur_token->next;
			if (cur_token != NULL && is_valid_word_token(cur_token))
			{
				cur_token = cur_token->next;
				if (cur_token != NULL && cur_token->type == T_SPACE)
				{
					prev_token = cur_token;
					cur_token = cur_token->next;
				}
			}
		}
		if (cur_token != NULL && (is_valid_word_token(cur_token)
				|| cur_token->type == T_SPACE))
		{
			if (cur_token->value[0] == '$' && cur_token->type != T_1Q_WORD)
				new_group->args[i] = ft_strdup("EXPAND");
			else
				new_group->args[i] = ft_strdup(cur_token->value);
			i++;
			process_arg_token(tokens, &cur_token, &prev_token, new_group);
		}
	}
	new_group->args[i] = NULL;
}
