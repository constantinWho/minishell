/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_quotes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chustei <chustei@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/03 19:38:35 by chustei           #+#    #+#             */
/*   Updated: 2023/07/03 20:09:15 by chustei          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	check_quotes(char *input)
{
	int	i;
	int	type;

	i = 0;
	type = 0;
	while (input[i])
	{
		if (input[i] == '"' || input[i] == '\'')
		{
			if (type == 0)
			{
				type = input[i];
				i++;
				while (input[i] && input[i] != type)
					i++;
				if (!input[i])
					return (0);
				type = 0;
			}
		}
		i++;
	}
	if (type != 0)
		return (0);
	return (1);
}
