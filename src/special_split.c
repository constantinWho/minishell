/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   special_split.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chustei <chustei@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/28 16:19:05 by chustei           #+#    #+#             */
/*   Updated: 2023/06/29 17:14:24 by chustei          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

char	*save_delimited_str(char *s, int *i)
{
	char	*saved;
	int		split;
	int		start;
	int		j;

	split = s[*i];
	start = *i;
	j = 0;
	(*i)++;
	while (s[*i] != split)
		(*i)++;
	(*i)++;
	saved = (char *)malloc((*i - start + 1) * sizeof(char *));
	if (!saved)
		return (NULL);
	while (start < *i)
	{
		saved[j] = s[start];
		j++;
		start++;
	}
	saved[j] = '\0';
	return (saved);
}

char	*save_regular_str(char *s, int *i)
{
	char	*saved;
	int		start;
	int		j;

	start = *i;
	j = 0;
	while (s[*i] && (s[*i] != '\t' && s[*i] != ' ' && !is_delimiter(s[*i])))
		(*i)++;
	saved = (char *)malloc((*i - start + 1) * sizeof(char *));
	while (start < *i)
	{
		saved[j] = s[start];
		j++;
		start++;
	}
	saved[j] = '\0';
	return (saved);
}

void	save_and_check_del(t_minishell *shell, char *s, int	*i, int *j)
{
	if (s[*i + 1] == s[*i])
		*i += 2;
	else
	{
		shell->args[*j] = save_delimited_str(s, i);
		(*j)++;
	}
}

void	save_and_check_reg(t_minishell *shell, char *s, int	*i, int *j)
{
	shell->args[*j] = save_regular_str(s, i);
	if (ft_strlen(shell->args[*j]) == 0)
		free(shell->args[*j]);
	else
		(*j)++;
}

void	special_split(t_minishell *shell, char *s)
{
	int		i;
	int		j;
	int		str_count;

	i = 0;
	j = 0;
	str_count = count_strs(s);
	shell->args = (char **)malloc((str_count + 1) * sizeof(char *));
	while (s[i])
	{
		i = skip_whitespace(s, i);
		if (is_delimiter(s[i]))
			save_and_check_del(shell, s, &i, &j);
		else
			save_and_check_reg(shell, s, &i, &j);
		if ((s[i] == ' ' || s[i] == '\t') && s[i + 1] && j < str_count)
		{
			shell->args[j] = ft_strdup(" ");
			j++;
		}
		i = skip_whitespace(s, i);
	}
	shell->args[j] = NULL;
}
