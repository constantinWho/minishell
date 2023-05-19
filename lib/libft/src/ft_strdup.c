/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chustei <chustei@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/05 19:01:35 by chustei           #+#    #+#             */
/*   Updated: 2023/03/02 13:01:34 by chustei          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"

char	*ft_strdup(const char *s)
{
	char	*p;
	int		i;

	i = -1;
	p = (char *)malloc(sizeof(char) * ft_strlen(s)+ 1);
	if (!p)
		return (NULL);
	while (s[++i])
		p[i] = s[i];
	p[i] = '\0';
	return (p);
}
