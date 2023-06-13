/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chustei <chustei@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/07 13:37:01 by chustei           #+#    #+#             */
/*   Updated: 2023/06/07 15:26:49 by chustei          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "shell.h"

void	print_prompt1(void)
{
	fprintf(stderr, "$ ");
}

void	print_prompt2(void)
{
	fprintf(stderr, "> ");
}
