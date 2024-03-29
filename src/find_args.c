/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_args.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chustei <chustei@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 13:31:30 by chustei           #+#    #+#             */
/*   Updated: 2023/08/02 16:16:33 by chustei          ###   ########.fr       */
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
			skip_redir_block(&cur_token);
		if (cur_token != NULL && is_valid_word_token(cur_token))
		{
			count++;
			cur_token = cur_token->next;
		}
		if (cur_token != NULL && cur_token->type == T_SPACE)
		{
			cur_token = cur_token->next;
			if (cur_token != NULL && cur_token->type != T_PIPE)
				count++;
		}
	}
	return (count);
}

void	process_arg_token(t_token **tokens, t_token **cur_token,
	t_token **prev_token)
{
	if (*prev_token != NULL)
		update_prev_token_next(prev_token, cur_token);
	else
		update_tokens_head(tokens, cur_token);
}

void	dup_and_save(t_token **cur_token, t_group **new_group, int *i,
	char **env)
{
	char	*env_str;

	if ((*cur_token)->value[0] == '$' && (*cur_token)->type != T_1Q_WORD)
	{
		env_str = get_env_str((*cur_token)->value, env);
		(*new_group)->args[*i] = ft_strdup(env_str);
		free(env_str);
	}
	else
		(*new_group)->args[*i] = ft_strdup((*cur_token)->value);
	(*i)++;
}

void	remove_last_space(t_group **new_group, int *i)
{
	if (*new_group == NULL || (*new_group)->args == NULL || *i <= 0)
		return ;
	if ((*new_group)->args[*i - 1][0] == ' '
		&& ft_strlen(&(*new_group)->args[*i - 1][0]) == 1)
	{
		free(&(*new_group)->args[*i - 1][0]);
		(*i)--;
	}
}

void	find_args(t_token **tokens, t_group *new_group, char **env)
{
	t_token	*cur_token;
	t_token	*prev_token;
	int		args_num;
	int		i;

	cur_token = *tokens;
	prev_token = NULL;
	args_num = count_args(*tokens);
	new_group->args = (char **)malloc((args_num + 1) * sizeof(char *));
	i = 0;
	while (cur_token != NULL && cur_token->type != T_PIPE)
	{
		if (is_redirection(cur_token))
			skip_redir_block_update_prev_token(&cur_token, &prev_token);
		if (cur_token != NULL && (is_valid_word_token(cur_token)
				|| cur_token->type == T_SPACE))
		{
			dup_and_save(&cur_token, &new_group, &i, env);
			process_arg_token(tokens, &cur_token, &prev_token);
		}
	}
	remove_last_space(&new_group, &i);
	new_group->args[i] = NULL;
}
