/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nde-sant <nde-sant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/07 10:59:11 by nde-sant          #+#    #+#             */
/*   Updated: 2026/02/13 16:57:03 by nde-sant         ###   ########.fr       */
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
	return(new_sh);
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
		while(cmds[i])
			free_cmd(cmds[i++]);
		free(cmds);
	}
	sh->cmds = NULL;
	sh->cmd_count = 0;
}

int	main(int argc, char **argv, char **envp)
{
	char	*line;
	t_shell	*sh;

	(void)argc;
	(void)argv;
	sh = init_shell(envp);
	line = "";
	while (line)
	{	
		line = readline("minishell> ");
		if (!line)
			break ;
		if (ft_strlen(line) > 0)
		{
			add_history(line);
			if(!parse(line, sh))
				executor(sh);
			reset_shell(sh);
		}
		free(line);
	}
	rl_clear_history();
	return (0);
}
