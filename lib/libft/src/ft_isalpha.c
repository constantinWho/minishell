/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalpha.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chustei <chustei@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 11:41:32 by chustei           #+#    #+#             */
/*   Updated: 2023/03/02 12:57:59 by chustei          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"

int	ft_isalpha(int c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
		return (1);
	return (0);
}

/* int main()
{
    int c;
    c = 'Q';
    printf("isalpha: %d\n", isalpha(c));
    printf("ft_isalpha: %d\n", ft_isalpha(c));
    c = 'q';
	printf("isalpha: %d\n", isalpha(c));
    printf("ft_isalpha: %d\n", ft_isalpha(c));
    c='+';
	printf("isalpha: %d\n", isalpha(c));
    printf("ft_isalpha: %d\n", ft_isalpha(c));
    return 0;
} */
