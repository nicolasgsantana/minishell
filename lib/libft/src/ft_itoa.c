/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nde-sant <nde-sant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/22 18:27:44 by nde-sant          #+#    #+#             */
/*   Updated: 2026/01/06 13:46:26 by nde-sant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_intlen(int n)
{
	size_t	size;
	long	number;

	number = (long)n;
	size = 0;
	if (number == 0)
		size++;
	else if (number < 0)
	{
		size++;
		number *= -1;
	}
	while (number > 0)
	{
		number /= 10;
		size++;
	}
	return (size);
}

char	*ft_itoa(int n)
{
	char	*result_str;
	long	number;
	int		i;
	int		sign;

	result_str = malloc((ft_intlen(n) + 1) * sizeof(char));
	if (!result_str)
		return (NULL);
	sign = 1;
	number = (long)n;
	i = ft_intlen(n);
	result_str[i--] = '\0';
	if (number == 0)
		result_str[i] = '0';
	else if (number < 0)
		sign *= -1;
	number *= sign;
	while (number > 0)
	{
		result_str[i--] = (number % 10) + '0';
		number /= 10;
	}
	if (sign < 0)
		result_str[i] = '-';
	return (result_str);
}
