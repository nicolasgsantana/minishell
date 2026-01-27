/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kqueiroz <kqueiroz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/14 19:18:45 by kqueiroz          #+#    #+#             */
/*   Updated: 2026/01/27 19:44:24 by kqueiroz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	*create_pipes(int cmd_count)
{
	int	*pipes;
	int	i;

	if (cmd_count <= 1)
		return (NULL);
	pipes = malloc(sizeof(int) * 2 * (cmd_count - 1));
	if (!pipes)
		return (NULL);
	i = 0;
	while (i < cmd_count - 1)
	{
		pipe(pipes + i * 2);
		i++;
	}
	return (pipes);
}

void	setup_pipes(int i, int cmd_count, int *pipes)
{
	if (i > 0)
		dup2(pipes[(i - 1) * 2], STDIN_FILENO);
	if (i < cmd_count - 1)
		dup2(pipes[i * 2 + 1], STDOUT_FILENO);
}

void	close_all_pipes(int *pipes, int cmd_count)
{
	int	i;

	if (!pipes)
		return ;
	i = 0;
	while (i < 2 * (cmd_count - 1))
	{
		close(pipes[i]);
		i++;
	}
}
