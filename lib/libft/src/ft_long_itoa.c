/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_long_itoa.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chustei <chustei@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/12 12:34:43 by chustei           #+#    #+#             */
/*   Updated: 2023/03/02 12:58:30 by chustei          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"

char	*ft_long_itoa(long long int n)
{
	char			*str;
	unsigned int	len;

	len = ft_intlen(n);
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
