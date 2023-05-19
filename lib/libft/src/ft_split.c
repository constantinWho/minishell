/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chustei <chustei@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/11 20:20:55 by chustei           #+#    #+#             */
/*   Updated: 2023/03/02 13:01:17 by chustei          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"

size_t	ft_findsize(const char *s, char c)
{
	size_t	size;

	size = 0;
	while (*s)
	{
		if (*s != c)
		{
			size++;
			while (*s && *s != c)
				s++;
		}
		else
		{
			s++;
		}
	}
	return (size);
}

char	**ft_split(char const *s, char c)
{
	size_t	i;
	size_t	len;
	char	**str;

	if (!s)
		return (NULL);
	i = 0;
	str = malloc(sizeof(char *) * (ft_findsize(s, c) + 1));
	if (!str)
		return (NULL);
	while (*s)
	{
		if (*s != c)
		{
			len = 0;
			while (*s && *s != c && ++len)
				s++;
			str[i++] = ft_substr(s - len, 0, len);
		}
		else
			s++;
	}
	str[i] = 0;
	return (str);
}
