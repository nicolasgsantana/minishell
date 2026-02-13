/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kqueiroz <kqueiroz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/17 14:18:28 by kqueiroz          #+#    #+#             */
/*   Updated: 2026/02/12 23:15:08 by kqueiroz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_numeric(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	if (str[i] == '+' || str[i] == '-')
		i++;
	while (str[i])
	{
		if ((!ft_isdigit(str[i])) || (i > 17))
			return (0);
		i++;
	}
	return (1);
}

int	ft_exit(t_shell *sh, t_cmd *cmd)
{
	int	nb;

	if (!cmd->argv[1])
	{
		printf("exit\n");
		exit(sh->last_status);
	}
	if (!is_numeric(cmd->argv[1]))
	{
		printf("exit\n");
		printf("minishell: exit: %s: numeric argument required\n",
			cmd->argv[1]);
		exit (2);
	}
	if (cmd->argv[2])
	{
		printf("exit\n");
		printf("minishell: exit: too many arguments\n");
		return (1);
	}
	nb = ft_atoi(cmd->argv[1]);
	printf("exit\n");
	exit((unsigned char)nb);
}
