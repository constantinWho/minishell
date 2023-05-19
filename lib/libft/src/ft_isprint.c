/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isprint.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chustei <chustei@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 16:26:59 by chustei           #+#    #+#             */
/*   Updated: 2023/03/02 12:58:18 by chustei          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"

int	ft_isprint(int c)
{
	if (c >= 32 && c <= 126)
		return (1);
	return (0);
}
/* int main()
{
    char c;

    c = 'Q';
    printf("%c is passed to isprint(): %d\n", c, isprint(c));
    printf("%c is passed to ft_isprint(): %d\n", c, ft_isprint(c));
    c = '\n';
    printf("%c is passed to isprint(): %d", c, isprint(c));
    printf("%c is passed to ft_isprint(): %d", c, ft_isprint(c));
    return 0;
} */
