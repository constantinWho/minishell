/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_args.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chustei <chustei@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 13:31:30 by chustei           #+#    #+#             */
/*   Updated: 2023/07/31 15:39:48 by chustei          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

/* int	get_split_num(char	*str)
{
	int	i;
	int	count;

	count = 0;
	i = 0;
	while (str[i])
	{
		if (str[i] != '$' && !str[i - 1])
			count++;
		while (str[i] && str[i] != '$')
			i++;
		if (str[i] == '$')
		{
			i++;
			count++;
		}
		while (str[i] && ft_isalnum(str[i]) == 1)
			i++;
		if (ft_isalnum(str[i]) == 0)
		{
			i++;
			if (str[i])
				count++;
		}
	}
	return (count);
} */

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
/* 			if (cur_token->type == T_2Q_WORD || cur_token->type == T_WORD)
				count += get_split_num(cur_token->value);
			else */
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

char	*get_env_str(char *arg, char **env)
{
	int		i;
	int		size;
	char	*new_str;

	i = 0;
	new_str = NULL;
	if (ft_strlen(arg) == 1)
		return (ft_strdup("$"));
	if (!ft_strncmp(arg, "$0", 2))
		return (ft_strdup("minishell"));
	if (!ft_strncmp(arg, "$?", 2))
		return (ft_strdup("$?"));
	if (ft_isdigit(arg[1]))
		return (ft_strdup(arg + 2));
	while (env[i])
	{
		size = 0;
		while (env[i][size] != '=')
			size++;
		if (!ft_strncmp(arg + 1, env[i], ft_strlen(arg) - 1)
			&& (size_t)size == ft_strlen(arg) - 1)
			new_str = ft_strdup(env[i] + size + 1);
		i++;
	}
	if (new_str == NULL)
		new_str = ft_strdup(arg + ft_strlen(arg));
	return (new_str);
}

void	dup_and_save(t_token **cur_token, t_group **new_group, int *i,
	char **env)
{
	char	*env_str;

	if ((*cur_token)->value[0] == '$' && (*cur_token)->type != T_1Q_WORD)
	{
		env_str = get_env_str((*cur_token)->value, env);
		(*new_group)->args[*i] = ft_strdup(env_str);
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

/* int	check_if_should_be_split(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '$')
			return (1);
		i++;
	}
	return (0);
}

void	split_and_save(char *str)
{
	int		i;
	int		j;
	int		c;
	char	*new_s;

	c = 0;
	i = 0;
	new_s = NULL;
	while (str[i])
	{
		if (str[i] != '$' && !str[i - 1])
		{
			j = i;
			printf("1ARG: %c\n", str[i]);
		}
		while (str[i] && str[i] != '$')
			i++;
		if (i > j)
		{
			c = 0;
			new_s = (char *)malloc(sizeof(char *) * (j - i + 1));
			while (c < j - i)
			{
				new_s[c] = new_s[j + c];
				c++;
			}
			dup_and_save(new_s);
		}
		if (str[i] == '$')
		{
			printf("2ARG: %c\n", str[i]);
			i++;
		}
		while (str[i] && ft_isalnum(str[i]) == 1)
			i++;
		if (ft_isalnum(str[i]) == 0)
		{
			if (str[i])
			{
				printf("2ARG: %c\n", str[i]);
			}
		}
	}
}
 */
void	find_args(t_token **tokens, t_group *new_group, char **env)
{
	t_token	*cur_token;
	t_token	*prev_token;
	int		args_num;
	int		i;

	cur_token = *tokens;
	prev_token = NULL;
	args_num = count_args(*tokens);
	//printf("ARGS num: %i\n", args_num);
	new_group->args = (char **)malloc((args_num + 1) * sizeof(char *));
	i = 0;
	while (cur_token != NULL && cur_token->type != T_PIPE)
	{
		if (is_redirection(cur_token))
			skip_redir_block_update_prev_token(&cur_token, &prev_token);
		if (cur_token != NULL && (is_valid_word_token(cur_token)
				|| cur_token->type == T_SPACE))
		{
/* 			if (cur_token != NULL && (is_valid_word_token(cur_token))
				&& check_if_should_be_split(cur_token->value) == 1)
				split_and_save(cur_token->value);
			else */
			dup_and_save(&cur_token, &new_group, &i, env);
			process_arg_token(tokens, &cur_token, &prev_token);
		}
	}
	remove_last_space(&new_group, &i);
	new_group->args[i] = NULL;
}
