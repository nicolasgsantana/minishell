/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ptrtohex.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nde-sant <nde-sant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 15:34:01 by nde-sant          #+#    #+#             */
/*   Updated: 2026/01/06 13:47:38 by nde-sant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_ptrtohex(void *ptr)
{
	uintptr_t	n;

	if (!ptr)
		return (NULL);
	n = (uintptr_t)ptr;
	return (ft_itohex(n, 0));
}
