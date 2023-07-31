/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lexer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chustei <chustei@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/03 20:09:40 by chustei           #+#    #+#             */
/*   Updated: 2023/07/31 19:27:40 by chustei          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	get_split_num(char	*str)
{
	int	i;
	int	count;

	count = 0;
	i = 0;
	while (str[i])
	{
		if (str[i] != '$')
		{
			while (str[i] && str[i] != '$')
				i++;
			if (str[i] == '$' || !str[i])
				count++;
		}
		else if (str[i] == '$')
		{
			i++;
			while (str[i] && ft_isalnum(str[i]) == 1 && str[i] != '$')
				i++;
			if (str[i] == '$' || ft_isalnum(str[i]) == 0 || !str[i])
				count++;
		}
		else if (ft_isalnum(str[i]) == 0)
		{
			while (str[i] && str[i] != '$')
				i++;
			if (str[i] == '$' || !str)
				count++;
		}
	}
	return (count);
}

char	**get_rest(char *str, char **dest)
{
	int	i;
	int	start;
	int	count;
	int	j;

	count = 0;
	i = 0;
	while (str[i])
	{
		if (str[i] != '$')
		{
			start = i;
			while (str[i] && str[i] != '$')
				i++;
			if (str[i] == '$' || !str[i])
			{
				j = 0;
				dest[count] = (char *)malloc(sizeof(char *) * (i - start + 1));
				while (start < i)
				{
					dest[count][j] = str[start];
					j++;
					start++;
				}
				dest[count][j] = '\0';
				count++;
			}
		}
		else if (str[i] == '$')
		{
			start = i;
			i++;
			while (str[i] && ft_isalnum(str[i]) == 1 && str[i] != '$')
				i++;
			if (str[i] == '$' || ft_isalnum(str[i]) == 0 || !str[i])
			{
				j = 0;
				dest[count] = (char *)malloc(sizeof(char *) * (i - start + 1));
				while (start < i)
				{
					dest[count][j] = str[start];
					j++;
					start++;
				}
				dest[count][j] = '\0';
				count++;
			}
		}
		else if (ft_isalnum(str[i]) == 0)
		{
			start = i;
			while (str[i] && str[i] != '$')
				i++;
			if (str[i] == '$' || !str)
			{
				j = 0;
				dest[count] = (char *)malloc(sizeof(char *) * (i - start + 1));
				while (start < i)
				{
					dest[count][j] = str[start];
					j++;
					start++;
				}
				dest[count][j] = '\0';
				count++;
			}
		}
	}
	dest[count] = NULL;
	return (dest);
}

char	**get_split_rest(char *str)
{
	char	*s_cpy;
	char	**split_rest;
	int		last_i;

	last_i = ft_strlen(str) - 1;
	s_cpy = NULL;
	split_rest = NULL;
	if (str[0] == '"' && str[last_i] == '"')
		s_cpy = ft_strtrim(str, "\"");
	else
		s_cpy = ft_strdup(str);
	split_rest = (char **)malloc(sizeof(char *) * (get_split_num(s_cpy) + 1));
	split_rest = get_rest(s_cpy, split_rest);
	return (split_rest);
}

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

void	ft_lexer(t_minishell *shell, char *input)
{
	int		i;
	int		j;
	char	**split_rest;

	if (!(check_quotes(input)))
		return ;
	special_split(shell, input);
	i = 0;
	split_rest = NULL;
	shell->tokens = NULL;
	while (shell->args[i])
	{
		if (check_if_should_be_split(shell->args[i]) == 1
			&& check_single_q(shell->args[i]) == 0)
		{
			j = 0;
			split_rest = get_split_rest(shell->args[i]);
			while (split_rest[j])
			{
				append_token(shell, split_rest[j]);
				free(split_rest[j]);
				j++;
			}
			free(split_rest);
		}
		else
			append_token(shell, shell->args[i]);
		i++;
	}
}
