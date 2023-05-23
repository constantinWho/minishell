/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chustei <chustei@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 16:54:52 by chustei           #+#    #+#             */
/*   Updated: 2023/05/23 16:55:10 by chustei          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

// needs functionality for "cd -" takes user back to previous position
// this is stored in the .env file
int	ft_cd(char **args)
{
	if (chdir(args[0]) != 0)
	{
		perror("chdir() error");
		return (1);
	}
	return (0);
}
