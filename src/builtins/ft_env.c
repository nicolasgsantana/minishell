/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kqueiroz <kqueiroz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/16 10:30:06 by kqueiroz          #+#    #+#             */
/*   Updated: 2026/01/27 19:45:48 by kqueiroz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_env(t_shell *sh)
{
	int	i;

	i = 0;
	while (sh->envp[i])
	{
		if (ft_strchr(sh->envp[i], '='))
		{
			if (sh->envp[i + 1])
				ft_putendl_fd(sh->envp[i], STDOUT_FILENO);
		}
		i++;
	}
	return (0);
}
