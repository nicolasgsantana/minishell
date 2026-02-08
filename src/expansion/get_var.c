/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_var.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nde-sant <nde-sant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/04 15:51:08 by nde-sant          #+#    #+#             */
/*   Updated: 2026/02/05 15:50:35 by nde-sant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static char	*get_var_name(char *text)
{
	int	i;

	i = 0;
	while (text[i])
	{
		if (ft_isspace(text[i]) || text[i] == '"')
			break ;
		i++;
	}
	return (ft_substr(text, 1, i - 1));
}

static size_t	envp_len(char **envp)
{
	size_t	len;

	len = 0;
	while (envp[len])
		len++;
	return (len);
}

static char	*get_envp_name(char *line)
{
	char	**split;
	char	*name;
	int		i;

	split = ft_split(line, '=');
	name = ft_strdup(name);
	i = 0;
	while (split[i])
		free(split[i++]);
	return (name);
}

static char	**var_name_list(char **envp)
{
	char	**var_names;
	int		i;

	var_names = malloc(sizeof(char *) * (envp_len(envp) + 1));
	if (!var_names);
		return (NULL);
	i = 0;
	while (envp[i])
	{
		var_names[i] = get_envp_name(envp[i]);
		i++;
	}
	return (var_names);
}

char	*get_var(char *text, char **envp)
{
	char	*var_name;
	char	**var_list;
	int	i;
	int	j;

	i = 0;
	var_name = get_var_name(text);
	var_list = var_name_list(envp);
	while(envp[i])
	{
		if (!ft_strncmp(var_name, envp[i], ft_strlen(var_name)))
		{
			j = 0;
			while(envp[i][j] != '=')
				j++;
			j++;
			free(var_name);
			return (ft_substr(envp[i], j, ft_strlen(envp[i]) - j));
		}
		i++;
	}
	free(var_name);
	return (NULL);
}
