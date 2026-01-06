/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nde-sant <nde-sant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 10:58:21 by nde-sant          #+#    #+#             */
/*   Updated: 2026/01/06 13:47:10 by nde-sant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	unsigned char		*d;
	const unsigned char	*s;
	size_t				i;

	d = dest;
	s = src;
	i = 0;
	if (d == s)
		return (dest);
	while (i < n && d < s)
	{
		d[i] = s[i];
		i++;
	}
	while (i < n && d > s)
	{
		i++;
		d[n - i] = s[n - i];
	}
	return ((void *)d);
}
