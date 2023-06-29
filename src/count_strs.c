/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   count_strs.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chustei <chustei@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 16:53:12 by chustei           #+#    #+#             */
/*   Updated: 2023/06/29 16:09:46 by chustei          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	skip_whitespace(char *s, int i)
{
	while ((s[i] == ' ' || s[i] == '\t') && s[i])
		i++;
	return (i);
}

int	is_delimiter(char c)
{
	return (c == '\'' || c == '"');
}

int	count_delimited_strs(char *s, int *i)
{
	int	count;
	int	split;
	int	pos;

	count = 0;
	split = s[*i];
	pos = *i;
	(*i)++;
	while (s[*i] != split)
		(*i)++;
	if (*i > pos + 1)
		count++;
	(*i)++;

	return (count);
}

int	count_regular_strs(char *s, int *i)
{
	int	count;
	int	pos;

	count = 0;
	pos = *i;
	while (s[*i] && (s[*i] != '\t' && s[*i] != ' ' && !is_delimiter(s[*i])))
		(*i)++;
	if (*i > pos)
		count++;

	return (count);
}

int	count_strs(char *s)
{
	int	i;
	int	split;
	int	count;
	int	pos;

	i = 0;
	count = 0;
	pos = -1;
	while (s[i])
	{
		split = 0;
		i = skip_whitespace(s, i);
		if (is_delimiter(s[i]))
			count += count_delimited_strs(s, &i);
		else
			count += count_regular_strs(s, &i);
		i = skip_whitespace(s, i);
		if ((s[i - 1] == ' ' || s[i - 1] == '\t') && count != 0 && s[i])
			count++;
	}
	return (count);
}
