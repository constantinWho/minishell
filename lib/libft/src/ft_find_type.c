/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_find_type.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chustei <chustei@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/28 10:53:28 by chustei           #+#    #+#             */
/*   Updated: 2023/03/02 12:57:44 by chustei          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"

int	ft_find_type(va_list args, char type)
{
	if (type == 'c')
		return (ft_putchar(va_arg(args, int)));
	else if (type == '%')
		return (ft_putchar('%'));
	else if (type == 's')
		return (ft_putstr(va_arg(args, char *)));
	else if (type == 'p')
		return (ft_putptr(va_arg(args, unsigned long long)));
	else if (type == 'd' || type == 'i')
		return (ft_putnbr(va_arg(args, int)));
	else if (type == 'u')
		return (ft_putnbr(va_arg(args, unsigned int)));
	else if (type == 'X' || type == 'x')
		return (ft_puthex(va_arg(args, unsigned int), type));
	return (-1);
}
