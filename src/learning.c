/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   learning.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chustei <chustei@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 10:39:55 by chustei           #+#    #+#             */
/*   Updated: 2023/05/19 12:33:20 by chustei          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//The readline() function reads a line from the terminal and returns it,
//using prompt as a prompt. If no prompt is given as parameter, no prompt
//will be shown in the terminal. The line returned is allocated with malloc
//and we have to free it ourselves.

#include "../inc/minishell.h"

void	ft_readline(void)
{
	char	*rl;

	rl = readline("Minishell > ");
	printf("%s\n", rl);
}

int	main(void)
{
//  compile with flag "-lreadline"
	ft_readline();
	printf("%i \n", history_length);
	return (0);
}
