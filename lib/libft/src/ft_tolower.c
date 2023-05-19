/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tolower.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chustei <chustei@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/29 12:08:52 by chustei           #+#    #+#             */
/*   Updated: 2023/03/02 13:02:47 by chustei          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"

int	ft_tolower(int c)
{
	if (c >= 65 && c <= 90)
		return (c + 32);
	else
		return (c);
}
/*
int main()
{
	char c = 'A';
	printf("%c turns in %c | %c\n", c, ft_lower(c), tolower(c));
	c = 'h';
	printf("%c turns in %c | %c\n", c, ft_lower(c), tolower(c));
	return (0);
}
 */
