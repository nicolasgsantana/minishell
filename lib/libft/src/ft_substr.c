/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nde-sant <nde-sant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/22 12:01:18 by nde-sant          #+#    #+#             */
/*   Updated: 2026/01/06 13:48:27 by nde-sant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*substr;
	size_t	i;
	size_t	s_len;
	size_t	new_len;

	s_len = ft_strlen(s);
	if (start > s_len)
		new_len = 0;
	else
		new_len = s_len - start;
	if (len > new_len)
		len = new_len;
	i = 0;
	substr = malloc((len + 1) * sizeof(char));
	if (!substr)
		return (0);
	while (i < len)
	{
		substr[i] = s[start + i];
		i++;
	}
	substr[i] = '\0';
	return (substr);
}
