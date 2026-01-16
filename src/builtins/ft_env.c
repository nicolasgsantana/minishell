/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keila <keila@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/16 10:30:06 by kqueiroz          #+#    #+#             */
/*   Updated: 2026/01/16 12:24:07 by keila            ###   ########.fr       */
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
			ft_putendl_fd(sh->envp[i], STDOUT_FILENO);
		i++;
	}
	return (0);
}
