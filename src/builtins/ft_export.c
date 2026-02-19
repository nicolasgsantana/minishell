/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kqueiroz <kqueiroz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/16 10:30:06 by kqueiroz          #+#    #+#             */
/*   Updated: 2026/02/19 15:42:27 by kqueiroz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*make_env_var(char *key, char *value)
{
	char	*tmp;
	char	*res;

	if (value == NULL)
		return (ft_strdup(key));
	tmp = ft_strjoin(key, "=");
	res = ft_strjoin(tmp, value);
	free(tmp);
	return (res);
}

int	add_env(char ***envp, char *key, char *value)
{
	int		len;
	char	**new_env;
	int		i;

	len = env_len(*envp);
	new_env = malloc(sizeof(char *) * (len + 2));
	if (!new_env)
		return (1);
	i = 0;
	while (i < len)
	{
		new_env[i] = ft_strdup((*envp)[i]);
		i++;
	}
	new_env[i] = make_env_var(key, value);
	new_env[i + 1] = NULL;
	i = 0;
	while ((*envp)[i])
	{
		free((*envp)[i]);
		i++;
	}
	free(*envp);
	*envp = new_env;
	return (0);
}

int	handle_export_arg(t_shell *sh, char *arg)
{
	char	*equal;
	char	*key;
	char	*value;

	if (!is_valid_identifier(arg))
	{
		ft_putstr_fd("minishell: export: ", 2);
		ft_putstr_fd(arg, 2);
		ft_putstr_fd(": not a valid identifier\n", 2);
		return (1);
	}
	equal = ft_strchr(arg, '=');
	if (equal)
	{
		key = ft_substr(arg, 0, equal - arg);
		value = equal + 1;
		if (!update_env(sh->envp, key, value))
			add_env(&sh->envp, key, value);
		free(key);
	}
	else
		add_env(&sh->envp, arg, NULL);
	return (0);
}

int	ft_export(t_shell *sh, t_cmd *cmd)
{
	int	i;

	if (!cmd->argv[1])
	{
		sort_env(sh->envp);
		print_export(sh->envp);
		return (0);
	}
	i = 1;
	while (cmd->argv[i])
	{
		if (handle_export_arg(sh, cmd->argv[i]))
			return (1);
		i++;
	}
	return (0);
}
