/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_uitoa.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nde-sant <nde-sant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/20 09:55:34 by nde-sant          #+#    #+#             */
/*   Updated: 2025/09/15 10:54:26 by nde-sant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_uintlen(unsigned int n)
{
	size_t	size;

	size = 0;
	if (n == 0)
		size++;
	while (n > 0)
	{
		n /= 10;
		size++;
	}
	return (size);
}

char	*ft_uitoa(unsigned int n)
{
	char	*result_str;
	int		i;

	result_str = malloc((ft_uintlen(n) + 1) * sizeof(char));
	if (!result_str)
		return (NULL);
	i = ft_uintlen(n);
	result_str[i--] = '\0';
	if (n == 0)
		result_str[i] = '0';
	while (n > 0)
	{
		result_str[i--] = (n % 10) + '0';
		n /= 10;
	}
	return (result_str);
}
