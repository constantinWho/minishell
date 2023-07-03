/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   word_split.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chustei <chustei@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/03 19:56:24 by chustei           #+#    #+#             */
/*   Updated: 2023/07/03 20:09:10 by chustei          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	save_double_symbs(char *str, char **words, int *i, int *j)
{
	if (str[*i] == '>')
		words[*j] = ft_strdup(">>");
	else if (str[*i] == '<')
		words[*j] = ft_strdup("<<");
	(*j)++;
	(*i) += 2;
}

void	save_single_symb(char *str, char **words, int *i, int *j)
{
	if (str[*i] == '>')
		words[*j] = ft_strdup(">");
	else if (str[*i] == '<')
		words[*j] = ft_strdup("<");
	else if (str[*i] == '|')
		words[*j] = ft_strdup("|");
	(*j)++;
	(*i)++;
}

void	save_rest(char *str, char **words, int *i, int *j)
{
	int	start;
	int	x;

	x = 0;
	start = *i;
	while (str[*i] && str[*i] != '<' && str[*i] != '>' && str[*i] != '|')
		(*i)++;
	if (*i - start != 0)
	{
		x = 0;
		words[*j] = (char *)malloc((*i - start + 1) * sizeof(char *));
		while (str[start] && str[start] != '<' && str[start] != '>'
			&& str[start] != '|')
		{
			words[*j][x] = str[start];
			x++;
			start++;
		}
		words[*j][x] = '\0';
		(*j)++;
	}
}

char	**word_split(char *str, int words_count)
{
	int		i;
	int		j;
	char	**words;

	words = (char **)malloc((words_count + 1) * sizeof(char *));
	i = 0;
	j = 0;
	while (str[i])
	{
		if ((str[i] == '>' && str[i + 1] == '>')
			|| (str[i] == '<' && str[i + 1] == '<'))
			save_double_symbs(str, words, &i, &j);
		else if (str[i] == '<' || str[i] == '>' || str[i] == '|')
			save_single_symb(str, words, &i, &j);
		else
			save_rest(str, words, &i, &j);
	}
	words[j] = NULL;
	return (words);
}
