/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_words_count.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chustei <chustei@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/03 19:53:12 by chustei           #+#    #+#             */
/*   Updated: 2023/07/03 19:55:58 by chustei          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	increment_double_symbs_count(int *i, int *count)
{
	(*i) += 2;
	(*count)++;
}

void	increment_single_symb_count(int *i, int *count)
{
	(*i)++;
	(*count)++;
}

void	increment_rest_count(char *str, int *i, int *count)
{
	int	start;

	start = *i;
	while (str[*i] && str[*i] != '<' && str[*i] != '>' && str[*i] != '|')
		(*i)++;
	if (*i - start != 0)
		(*count)++;
}

int	get_words_count(char *str)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (str[i])
	{
		if ((str[i] == '>' && str[i + 1] == '>')
			|| (str[i] == '<' && str[i + 1] == '<'))
			increment_double_symbs_count(&i, &count);
		else if (str[i] == '<' || str[i] == '>' || str[i] == '|')
			increment_single_symb_count(&i, &count);
		else
			increment_rest_count(str, &i, &count);
	}
	return (count);
}
