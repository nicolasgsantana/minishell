/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kqueiroz <kqueiroz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/07 10:59:11 by nde-sant          #+#    #+#             */
/*   Updated: 2026/02/20 12:05:21 by kqueiroz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_shell	*init_shell(char **envp)
{
	t_shell	*new_sh;

	new_sh = malloc(sizeof(t_shell));
	if (!new_sh)
		return (NULL);
	new_sh->cmds = NULL;
	new_sh->cmd_count = 0;
	new_sh->envp = dup_env(envp);
	new_sh->last_status = 0;
	return (new_sh);
}

void	free_cmd(t_cmd *cmd)
{
	int	i;

	i = 0;
	if (cmd->argv)
	{
		while (cmd->argv[i])
			free(cmd->argv[i++]);
		free(cmd->argv);
	}
	i = 0;
	if (cmd->hd_delim)
	{
		while (cmd->hd_delim[i])
			free(cmd->hd_delim[i++]);
		free(cmd->hd_delim);
	}
	free(cmd->input_file);
	free(cmd->output_file);
	free(cmd);
}

void	reset_shell(t_shell *sh)
{
	t_cmd	**cmds;
	int		i;

	cmds = sh->cmds;
	i = 0;
	if (cmds)
	{
		while (cmds[i])
		{
			if (cmds[i]->hd_count > 0)
				cleanup_hd(cmds[i]);
			free_cmd(cmds[i++]);
		}
		free(cmds);
	}
	sh->cmds = NULL;
	sh->cmd_count = 0;
}

void	free_sh(t_shell *sh)
{
	int	i;

	reset_shell(sh);
	i = 0;
	while (sh->envp[i])
		free(sh->envp[i++]);
	free(sh->envp);
	free(sh);
	close_all_fds_except_std();
	rl_clear_history();
}

int	main(int argc, char **argv, char **envp)
{
	char	*line;
	t_shell	*sh;

	(void)argc;
	(void)argv;
	setup_signals();
	sh = init_shell(envp);
	while (1)
	{
		line = readline("minishell> ");
		if (!line)
			sig_exit(sh);
		if (ft_strlen(line) > 0 && !is_line_whitespace(line))
		{
			add_history(line);
			if (!parse(line, sh))
				executor(sh);
			reset_shell(sh);
		}
	}
	return (0);
}
