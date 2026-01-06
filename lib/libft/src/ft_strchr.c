/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nde-sant <nde-sant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 17:49:08 by nde-sant          #+#    #+#             */
/*   Updated: 2025/07/24 17:40:17 by nde-sant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

char	*ft_strchr(const char *s, int c)
{
	int				i;
	unsigned char	to_find;

	to_find = c;
	i = 0;
	while (s[i] != to_find && s[i] != '\0')
		i++;
	if (s[i] == to_find)
		return ((char *)&s[i]);
	else
		return (0);
}
