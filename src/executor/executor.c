/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keila <keila@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/14 19:18:45 by kqueiroz          #+#    #+#             */
/*   Updated: 2026/01/08 05:37:07 by keila            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	execute_pipeline(t_shell *sh)
{
	int		*pipes;
	pid_t	pid;
	int		i;

	pipes = create_pipes(sh->cmd_count);
	i = 0;
	while (i < sh->cmd_count)
	{
		pid = fork();
		if (pid == 0)
			child_process(i, sh, pipes);
		i++;
	}
	close_all_pipes(pipes, sh->cmd_count);
	free(pipes);
	return (wait_for_children());
}

void	executor(t_shell *sh)
{
	//if (sh->cmd_count == 1 && sh->cmds[0].is_builtin)
	//	sh->last_status = exec_builtin(sh, &sh->cmds[0]);
	//else
	sh->last_status = execute_pipeline(sh);
}
