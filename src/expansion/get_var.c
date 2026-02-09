/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_var.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nde-sant <nde-sant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/04 15:51:08 by nde-sant          #+#    #+#             */
/*   Updated: 2026/02/09 14:11:19 by nde-sant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

char	*get_var_name(char *text)
{
	int	i;

	i = 0;
	if (text[i] == '$')
		i++;
	if (text[i] == '?')
		return (ft_strdup("?"));
	while (text[i])
	{
		if (!valid_name_char(text[i]))
			break ;
		i++;
	}
	return (ft_substr(text, 1, i - 1));
}

char	*get_last_status(char *var_name, int last_status)
{
	free(var_name);
	return (ft_strdup(ft_itoa(last_status)));
}

char	*get_var(char *text, t_shell *sh)
{
	char	*var_name;
	int		i;
	size_t	j;

	i = 0;
	var_name = get_var_name(text);
	if (var_name[0] == '?')
		return (get_last_status(var_name, sh->last_status));
	while (sh->envp[i])
	{
		j = 0;
		while (sh->envp[i][j] != '=')
			j++;
		if (j < ft_strlen(var_name))
			j = ft_strlen(var_name);
		if (!ft_strncmp(var_name, sh->envp[i], j++))
		{
			free(var_name);
			return (ft_substr(sh->envp[i], j, ft_strlen(sh->envp[i]) - j));
		}
		i++;
	}
	free(var_name);
	return (NULL);
}
