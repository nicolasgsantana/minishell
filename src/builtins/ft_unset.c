/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kqueiroz <kqueiroz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/17 13:26:06 by kqueiroz          #+#    #+#             */
/*   Updated: 2026/02/10 16:28:09 by kqueiroz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	remove_env(char ***envp, char *key)
{
	int		i;
	int		j;
	int		len;
	char	**new_env;

	i = find_env_index(*envp, key);
	if (i == -1)
		return (0);
	len = env_len(*envp);
	new_env = malloc(sizeof(char *) * len);
	j = 0;
	while (j < len)
	{
		if (j < i)
			new_env[j] = (*envp)[j];
		else if (j > i)
			new_env[j - 1] = (*envp)[j];
		j++;
	}
	new_env[len - 1] = NULL;
	free((*envp)[i]);
	free(*envp);
	*envp = new_env;
	return (0);
}

int	ft_unset(t_shell *sh, t_cmd *cmd)
{
	int	i;

	i = 1;
	while (cmd->argv[i])
	{
		remove_env(&sh->envp, cmd->argv[i]);
		i++;
	}
	return (0);
}
