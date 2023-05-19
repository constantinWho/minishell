/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isascii.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chustei <chustei@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 16:13:21 by chustei           #+#    #+#             */
/*   Updated: 2023/03/02 12:58:04 by chustei          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"

int	ft_isascii(int c)
{
	if (c >= 0 && c <= 127)
		return (1);
	return (0);
}
/* int main()
{
    char c;
    c = '5';
    printf("%c is passed, isascii returns: %d\n", c, isascii(c));
    printf("%c is passed, ft_isascii returns: %d\n", c, ft_isascii(c));
    c = 'Q';
    printf("%c is passed, isascii returns: %d\n", c, isascii(c));
    printf("%c is passed, ft_isascii returns: %d\n", c, ft_isascii(c));
    c = 'l';
    printf("%c is passed, isascii returns: %d\n", c, isascii(c));
    printf("%c is passed, ft_isascii returns: %d\n", c, ft_isascii(c));
    c = -1;
	printf("%c is passed, isascii returns: %d\n", c, isascii(c));
    printf("%c is passed, ft_isascii returns: %d\n", c, ft_isascii(c));
	c = 128;
	printf("%c is passed, isascii returns: %d\n", c, isascii(c));
    printf("%c is passed, ft_isascii returns: %d\n", c, ft_isascii(c));
    return 0;
} */
