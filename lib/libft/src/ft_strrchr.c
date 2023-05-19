/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chustei <chustei@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 13:07:02 by chustei           #+#    #+#             */
/*   Updated: 2023/03/02 13:02:34 by chustei          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"

char	*ft_strrchr(const char *s, int c)
{
	char	*ptr;

	ptr = NULL;
	while (*s != '\0')
	{
		if (*s == (c % 256))
			ptr = (char *)s;
		s++;
	}
	if (c == '\0')
		return ((char *)s);
	return (ptr);
}
