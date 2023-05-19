/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstiter.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chustei <chustei@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/13 19:42:48 by chustei           #+#    #+#             */
/*   Updated: 2023/03/02 12:58:54 by chustei          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"

void	ft_lstiter(t_list *lst, void (*f)(void *))
{
	t_list	*iter;

	if (!lst || !f)
		return ;
	iter = lst;
	while (lst)
	{
		(*f)(iter->content);
		iter = iter->next;
		if (!iter)
			return ;
	}
}
