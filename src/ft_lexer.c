/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lexer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chustei <chustei@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/03 20:09:40 by chustei           #+#    #+#             */
/*   Updated: 2023/08/10 11:00:59 by chustei          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	check_if_should_be_split(char *str)
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

int	check_single_q(char *str)
{
	int	last_i;

	last_i = ft_strlen(str) - 1;
	if (str[0] == '\'' && str[last_i] == '\'')
		return (1);
	else
		return (0);
}

void	split_append_free(char *src, char ***dest, t_minishell *shell)
{
	int	j;

	*dest = get_split_rest(src);
	j = 0;
	while ((*dest)[j])
	{
		append_token(shell, (*dest)[j]);
		free((*dest)[j]);
		j++;
	}
	free(*dest);
}

void	free_tokens(t_token *lst)
{
	t_token	*cur;
	t_token	*next;

	next = NULL;
	cur = lst;
	while (cur)
	{
		free(cur->value);
		next = cur->next;
		free(cur);
		cur = next;
	}
}

int	ft_lexer(t_minishell *shell, char *input)
{
	int		i;
	char	**split_rest;

	if (!(check_quotes(input)))
		return (0);
	special_split(shell, input);
	i = 0;
	split_rest = NULL;
	shell->tokens = NULL;
	while (shell->args[i])
	{
		if (check_if_should_be_split(shell->args[i]) == 1
			&& check_single_q(shell->args[i]) == 0)
			split_append_free(shell->args[i], &split_rest, shell);
		else
			append_token(shell, shell->args[i]);
		i++;
	}
	return (1);
}
