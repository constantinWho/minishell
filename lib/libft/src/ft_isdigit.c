/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isdigit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chustei <chustei@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 13:53:55 by chustei           #+#    #+#             */
/*   Updated: 2023/03/02 12:58:11 by chustei          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"

int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}
/*
int main()
{
    char c;
    c='5';
    printf("isdigit: %d\n", isdigit(c));
    printf("ft_isdigit: %d\n", ft_isdigit(c));
    c='+';
	printf("isdigit: %d\n", isdigit(c));
    printf("ft_isdigit: %d\n", ft_isdigit(c));
    return 0;
} */
