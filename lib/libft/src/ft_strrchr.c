/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nde-sant <nde-sant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 18:40:00 by nde-sant          #+#    #+#             */
/*   Updated: 2025/07/24 17:39:57 by nde-sant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

char	*ft_strrchr(const char *s, int c)
{
	int				i;
	int				last_found_index;
	unsigned char	to_find;

	last_found_index = -1;
	i = 0;
	to_find = c;
	while (s[i] != '\0')
	{
		if (s[i] == to_find)
			last_found_index = i;
		i++;
	}
	if (to_find == 0)
		last_found_index = i;
	if (last_found_index != -1)
		return ((char *)&s[last_found_index]);
	return (0);
}
