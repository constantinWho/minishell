/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chustei <chustei@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/12 12:34:43 by chustei           #+#    #+#             */
/*   Updated: 2023/03/02 12:58:24 by chustei          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"

size_t	ft_nlen(int n)
{
	size_t	i;

	i = 0;
	if (n == -2147483648)
		return (11);
	else if (n < 0)
	{
		i++;
		n = -n;
	}
	while (n > 0)
	{
		i++;
		n /= 10;
	}
	return (i);
}

char	*ft_itoa(int n)
{
	char	*str;
	size_t	len;

	if (n == -2147483648)
		return (ft_strdup("-2147483648"));
	else if (n == 0)
		return (ft_strdup("0"));
	len = ft_nlen(n);
	str = (char *)malloc(sizeof(char) * (len + 1));
	if (!str)
		return (0);
	if (n < 0)
	{
		n = -n;
		str[0] = '-';
	}
	str[len--] = '\0';
	while (n > 0)
	{
		str[len--] = (n % 10) + '0';
		n = n / 10;
	}
	return (str);
}
