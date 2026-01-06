/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nde-sant <nde-sant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/28 16:46:52 by nde-sant          #+#    #+#             */
/*   Updated: 2026/01/06 13:46:55 by nde-sant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*new_list;
	t_list	*last_node;

	new_list = ft_lstnew(f(lst -> content));
	if (!new_list)
	{
		ft_lstclear(&new_list, del);
		return (NULL);
	}
	lst = lst -> next;
	while (lst)
	{
		ft_lstadd_back(&new_list, ft_lstnew(f(lst -> content)));
		last_node = ft_lstlast(new_list);
		if (!last_node)
		{
			ft_lstclear(&new_list, del);
			return (NULL);
		}
		lst = lst -> next;
	}
	return (new_list);
}
