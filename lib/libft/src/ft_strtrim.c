/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nde-sant <nde-sant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/22 18:19:08 by nde-sant          #+#    #+#             */
/*   Updated: 2026/01/06 13:48:24 by nde-sant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_match_set_from_begining(const char *str, const char *set)
{
	int	count;
	int	i;
	int	j;

	count = 0;
	i = 0;
	j = 0;
	while (set[j] && str[i])
	{
		if (str[i] == set[j])
		{
			count++;
			i++;
			j = -1;
		}
		j++;
	}
	return (count);
}

static int	ft_match_set_from_end(const char *str, const char *set)
{
	int	count;
	int	i;
	int	j;

	count = 0;
	i = ft_strlen(str) - 1;
	j = ft_strlen(set) - 1;
	while (j >= 0 && i >= 0)
	{
		if (str[i] == set[j])
		{
			count++;
			i--;
			j = ft_strlen(set);
		}
		j--;
	}
	return (count);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	int		start_sets;
	int		end_sets;
	char	*trimmed_str;
	int		new_str_len;

	start_sets = ft_match_set_from_begining(s1, set);
	end_sets = ft_match_set_from_end(s1, set);
	new_str_len = ft_strlen(s1) - (start_sets + end_sets);
	if (new_str_len < 0)
		new_str_len = 0;
	trimmed_str = malloc((new_str_len + 1) * sizeof(char));
	if (!trimmed_str)
		return (NULL);
	ft_strlcpy(trimmed_str, s1 + start_sets, new_str_len + 1);
	return (trimmed_str);
}
