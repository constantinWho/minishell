/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chustei <chustei@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/13 19:31:01 by chustei           #+#    #+#             */
/*   Updated: 2023/03/02 12:58:46 by chustei          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*clear;

	if (!lst)
		return ;
	while (*lst)
	{
		clear = (*lst)->next;
		ft_lstdelone(*lst, del);
		(*lst) = clear;
	}
}
