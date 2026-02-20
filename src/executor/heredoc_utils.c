/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kqueiroz <kqueiroz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/14 13:09:07 by kqueiroz          #+#    #+#             */
/*   Updated: 2026/02/20 12:06:01 by kqueiroz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*hd_filename(int i)
{
	char	*num;
	char	*tmp;

	num = ft_itoa(i);
	tmp = ft_strjoin(".heredoc_", num);
	free(num);
	return (tmp);
}

int	hd_sigint(char *line, struct sigaction *old_sig)
{
	g_signal = 0;
	if (line)
		free(line);
	rl_replace_line("", 0);
	rl_on_new_line();
	restore_heredoc_signal(old_sig);
	return (130);
}

int	is_hd_delim(char *line, t_cmd *cmd, int index)
{
	if (!line)
	{
		warning_hd(cmd, index);
		return (1);
	}
	if (!ft_strncmp(line, cmd->hd_delim[index],
			ft_strlen(cmd->hd_delim[index]) + 1))
	{
		free(line);
		return (1);
	}
	return (0);
}
