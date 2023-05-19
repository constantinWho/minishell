/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_toupper.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chustei <chustei@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/29 11:22:17 by chustei           #+#    #+#             */
/*   Updated: 2023/03/02 13:02:54 by chustei          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"

int	ft_toupper(int c)
{
	if (c >= 'a' && c <= 'z')
		return (c - 32);
	return (c);
}
/*
int main()
{
	char c = '9';
	printf("%c turns in %c | %c\n", c, ft_toupper(c), toupper(c));
	c = 'h';
	printf("%c turns in %c | %c\n", c, ft_toupper(c), toupper(c));
	return (0);
}
 */
