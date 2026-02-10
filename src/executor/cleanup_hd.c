/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup_hd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kqueiroz <kqueiroz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/10 14:31:31 by kqueiroz          #+#    #+#             */
/*   Updated: 2026/02/10 14:32:14 by kqueiroz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	cleanup_hd(t_cmd *cmd)
{
	int		i;
	char	*num;
	char	*filename;

	i = 0;
	while (i < cmd->hd_count)
	{
		num = ft_itoa(i);
		filename = ft_strjoin("/tmp/.heredoc_", num);
		free(num);
		unlink(filename);
		free(filename);
		i++;
	}
}
