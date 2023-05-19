/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_puthex.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chustei <chustei@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/27 10:38:02 by chustei           #+#    #+#             */
/*   Updated: 2023/03/02 13:00:36 by chustei          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"

int	ft_check_x(char c)
{
	if (c == 'x')
		return (87);
	else if (c == 'X')
		return (55);
	return (0);
}

int	ft_puthex(unsigned long long n, char c)
{
	char	hex[50];
	int		i;
	int		rem;

	i = 0;
	rem = 0;
	if (n == 0)
	{
		ft_putchar('0');
		return (1);
	}
	while (n != 0)
	{
		rem = n % 16;
		if (rem < 10)
			hex[i] = rem + 48;
		else
			hex[i] = rem + ft_check_x(c);
		i++;
		n = n / 16;
	}
	ft_putstrrev(hex, i);
	return (i);
}
