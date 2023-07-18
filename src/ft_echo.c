/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalbers <jalbers@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/05 12:39:11 by jalbers           #+#    #+#             */
/*   Updated: 2023/07/05 17:19:32 by jalbers          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	ft_echo(char **args)
{
	int	i;
	int	j;
	int	new_line_option;

	i = 2;
	new_line_option = 1;
	if (args[i] && str_match(args[2], "-n") == 1)
	{
		i += 2;
		new_line_option = 0;
	}
	while (args[i])
	{
		j = 0;
		while (args[i][j])
			write(1, &args[i][j++], 1);
		i++;
	}
	if (new_line_option == 1)
		write(1, "\n", 1);
	return (0);
}
