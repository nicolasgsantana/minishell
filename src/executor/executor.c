/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kqueiroz <kqueiroz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/14 19:18:45 by kqueiroz          #+#    #+#             */
/*   Updated: 2026/02/13 21:28:52 by kqueiroz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	close_all_fds_except_std(void)
{
	int	fd;

	fd = 3;
	while (fd < 256)
	{
		close(fd);
		fd++;
	}
}

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
	close_all_fds_except_std();
	return (wait_for_children());
}

int	execute_builtin(t_shell *sh, t_cmd *cmd)
{
	if (!ft_strncmp(cmd->argv[0], "echo", 5))
		return (ft_echo(cmd));
	if (!ft_strncmp(cmd->argv[0], "cd", 3))
		return (ft_cd(sh, cmd));
	if (!ft_strncmp(cmd->argv[0], "pwd", 4))
		return (ft_pwd());
	if (!ft_strncmp(cmd->argv[0], "env", 4))
		return (ft_env(sh));
	if (!ft_strncmp(cmd->argv[0], "export", 7))
		return (ft_export(sh, cmd));
	if (!ft_strncmp(cmd->argv[0], "unset", 6))
		return (ft_unset(sh, cmd));
	if (!ft_strncmp(cmd->argv[0], "exit", 5))
		return (ft_exit(sh, cmd));
	return (1);
}

int	builtin_redir(t_shell *sh, t_cmd *cmd)
{
	int	save_stdin;
	int	save_stdout;
	int	status;

	save_stdin = dup(STDIN_FILENO);
	save_stdout = dup(STDOUT_FILENO);
	if (apply_redir(cmd))
	{
		dup2(save_stdin, STDIN_FILENO);
		dup2(save_stdout, STDOUT_FILENO);
		close(save_stdin);
		close(save_stdout);
		return (1);
	}
	status = execute_builtin(sh, cmd);
	dup2(save_stdin, STDIN_FILENO);
	dup2(save_stdout, STDOUT_FILENO);
	close(save_stdin);
	close(save_stdout);
	return (status);
}

void	executor(t_shell *sh)
{
	int	i;

	i = 0;
	while (i < sh->cmd_count)
	{
		if (sh->cmds[i]->hd_count > 0)
			sh->last_status = prepare_heredocs(sh->cmds[i], sh);
		i++;
	}
	if (sh->cmd_count == 1 && (sh->cmds[0])->is_builtin)
		sh->last_status = builtin_redir(sh, sh->cmds[0]);
	else
		sh->last_status = execute_pipeline(sh);
}
