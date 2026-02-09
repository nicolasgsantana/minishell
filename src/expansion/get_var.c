/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_var.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nde-sant <nde-sant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/04 15:51:08 by nde-sant          #+#    #+#             */
/*   Updated: 2026/02/09 12:02:56 by nde-sant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

char	*get_var_name(char *text)
{
	int	i;

	i = 0;
	if (text[i] == '$')
		i++;
	while (text[i])
	{
		if (!valid_name_char(text[i]))
			break ;
		i++;
	}
	return (ft_substr(text, 1, i - 1));
}

char	*get_var(char *text, char **envp)
{
	char	*var_name;
	int		i;
	size_t	j;

	i = 0;
	var_name = get_var_name(text);
	while(envp[i])
	{
		j = 0;
		while(envp[i][j] != '=')
			j++;
		if (j < ft_strlen(var_name))
			j = ft_strlen(var_name);
		if (!ft_strncmp(var_name, envp[i], j++))
		{
			free(var_name);
			return (ft_substr(envp[i], j, ft_strlen(envp[i]) - j));
		}
		i++;
	}
	free(var_name);
	return (NULL);
}
