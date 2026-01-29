/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kqueiroz <kqueiroz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/14 19:37:55 by kqueiroz          #+#    #+#             */
/*   Updated: 2026/01/28 17:30:12 by kqueiroz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	child_process(int i, t_shell *sh, int *pipes)
{
	if (pipes)
	{
		setup_pipes(i, sh->cmd_count, pipes);
		close_all_pipes(pipes, sh->cmd_count);
	}
	if (apply_redir(&sh->cmds[i]))
		exit(1);
	if (sh->cmds[i].is_builtin)
		exit(execute_builtin(sh, &sh->cmds[i]));
	execute_cmd(&sh->cmds[i], sh);
}

int	wait_for_children(void)
{
	int	status;
	int	last_status;

	last_status = 0;
	while (wait(&status) > 0)
	{
		if (WIFEXITED(status))
			last_status = WEXITSTATUS(status);
	}
	return (last_status);
}
