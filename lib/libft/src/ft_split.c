/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nde-sant <nde-sant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/22 18:26:28 by nde-sant          #+#    #+#             */
/*   Updated: 2026/01/06 13:47:58 by nde-sant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_count_strings(char const *str, char delimiter)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (str[i])
	{
		if (str[i] != delimiter && (str[i + 1] == delimiter || !str[i + 1]))
			count++;
		i++;
	}
	return (count);
}

static char	*get_index_str(char const *str, char delimiter, int index)
{
	int		i;
	int		current_index;
	int		str_len;
	int		str_index;
	char	*new_str;

	current_index = 0;
	i = 0;
	str_len = 0;
	str_index = -1;
	while (str[i])
	{
		if (str[i] != delimiter && current_index == index && str_index == -1)
			str_index = i;
		if (str[i] != delimiter && current_index == index)
			str_len++;
		if (str[i] != delimiter && (str[i + 1] == delimiter || !str[i + 1]))
			current_index++;
		i++;
	}
	new_str = malloc((str_len + 1) * sizeof(char));
	if (!new_str)
		return (NULL);
	ft_strlcpy(new_str, &str[str_index], str_len + 1);
	return (new_str);
}

static void	free_all(char **array)
{
	int	i;

	i = 0;
	while (array[i] != NULL)
	{
		free(array[i]);
		i++;
	}
	free(array);
	array = NULL;
}

char	**ft_split(char const *s, char c)
{
	char	**array;
	int		i;
	int		array_size;

	if (!s)
		return (NULL);
	array_size = ft_count_strings(s, c) + 1;
	array = malloc(array_size * sizeof(char *));
	if (!array)
		return (NULL);
	i = 0;
	while (i < array_size - 1)
	{
		array[i] = get_index_str(s, c, i);
		if (array[i] == NULL)
			free_all(array);
		i++;
	}
	array[i] = NULL;
	return (array);
}
