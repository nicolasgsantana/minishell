/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstlast.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nde-sant <nde-sant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/28 12:21:10 by nde-sant          #+#    #+#             */
/*   Updated: 2025/07/28 13:40:10 by nde-sant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstlast(t_list *lst)
{
	t_list	*last_node;

	last_node = lst;
	if (!last_node)
		return (NULL);
	while (lst -> next)
	{
		last_node = lst -> next;
		lst = lst -> next;
	}
	return (last_node);
}
