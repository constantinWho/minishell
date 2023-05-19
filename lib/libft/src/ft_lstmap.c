/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chustei <chustei@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/13 20:00:13 by chustei           #+#    #+#             */
/*   Updated: 2023/03/02 12:59:19 by chustei          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*node;
	t_list	*new_list;

	if (!lst || !f || !del)
		return (0);
	node = NULL;
	while (lst)
	{
		new_list = ft_lstnew(f(lst->content));
		if (!new_list)
		{
			ft_lstclear(&node, del);
			return (0);
		}
		ft_lstadd_back(&node, new_list);
		lst = lst->next;
	}
	return (node);
}
