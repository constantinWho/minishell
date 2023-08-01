/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_split_rest_num.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chustei <chustei@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/01 14:28:54 by chustei           #+#    #+#             */
/*   Updated: 2023/08/01 14:52:23 by chustei          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"


void	get_str_count(char *str, int *i, int *count)
{
	while (str[*i] && str[*i] != '$')
		(*i)++;
	if (str[*i] == '$' || !str[*i])
		(*count)++;
}

void	get_dolar_count(char *str, int *i, int *count)
{
	(*i)++;
	while (str[*i] && ft_isalnum(str[*i]) == 1 && str[*i] != '$')
		(*i)++;
	if (str[*i] == '$' || ft_isalnum(str[*i]) == 0 || !str[*i])
		(*count)++;
}

void	get_rest_count(char *str, int *i, int *count)
{
	while (str[*i] && str[*i] != '$')
		(*i)++;
	if (str[*i] == '$' || !str)
		(*count)++;
}

int	get_split_num_rest(char	*str)
{
	int	i;
	int	count;

	count = 0;
	i = 0;
	while (str[i])
	{
		if (str[i] != '$')
			get_str_count(str, &i, &count);
		else if (str[i] == '$')
			get_dolar_count(str, &i, &count);
		else if (ft_isalnum(str[i]) == 0)
			get_rest_count(str, &i, &count);

	}
	return (count);
}
