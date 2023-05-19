/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chustei <chustei@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/23 14:20:34 by chustei           #+#    #+#             */
/*   Updated: 2023/03/02 13:00:46 by chustei          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"

int	ft_putnbr(long long int n)
{
	char	*str;

	if (n == 0)
		return (ft_putchar('0'));
	str = ft_long_itoa(n);
	ft_putstr(str);
	free(str);
	return (ft_intlen(n));
}
