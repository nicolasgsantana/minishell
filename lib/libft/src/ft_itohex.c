/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itohex.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nde-sant <nde-sant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 09:14:25 by nicolas           #+#    #+#             */
/*   Updated: 2026/01/06 13:46:29 by nde-sant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_uitohex_len(uintptr_t n)
{
	size_t	size;

	size = 0;
	if (n == 0)
		size++;
	while (n > 0)
	{
		n /= 16;
		size++;
	}
	return (size);
}

char	*ft_itohex(uintptr_t n, int is_uppercase)
{
	char	*hex_chars;
	char	*converted;
	size_t	hex_len;

	if (is_uppercase)
		hex_chars = "0123456789ABCDEF";
	else
		hex_chars = "0123456789abcdef";
	hex_len = ft_uitohex_len(n);
	converted = malloc((hex_len + 1) * sizeof(char));
	if (!converted)
		return (NULL);
	converted[hex_len--] = '\0';
	if (n == 0)
		converted[hex_len] = '0';
	while (n > 0)
	{
		converted[hex_len--] = hex_chars[n % 16];
		n /= 16;
	}
	return (converted);
}
