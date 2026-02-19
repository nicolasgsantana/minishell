/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kqueiroz <kqueiroz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/17 14:18:28 by kqueiroz          #+#    #+#             */
/*   Updated: 2026/02/19 16:15:29 by kqueiroz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	error_message_and_clean(char *str, t_shell *sh)
{
	ft_putstr_fd(str, STDERR_FILENO);
	free_sh(sh);
}

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
		nb = sh->last_status;
		error_message_and_clean("exit\n", sh);
		exit(nb);
	}
	if (!is_numeric(cmd->argv[1]))
	{
		ft_putstr_fd("exit\nminishell: exit: ", 2);
		ft_putstr_fd(cmd->argv[1], 2);
		ft_putstr_fd(": numeric argument required", 2);
		error_message_and_clean("\n", sh);
		exit (2);
	}
	if (cmd->argv[2])
	{
		ft_putstr_fd("exit\nminishell: exit: too many arguments\n", 2);
		return (1);
	}
	nb = ft_atoi(cmd->argv[1]);
	ft_putstr_fd("exit\n", 1);
	exit((unsigned char)nb);
}
