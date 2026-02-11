/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nde-sant <nde-sant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/07 10:59:11 by nde-sant          #+#    #+#             */
/*   Updated: 2026/02/11 13:39:57 by nde-sant         ###   ########.fr       */
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
			parse(line, sh);
			executor(sh);
		}
		free(line);
	}
	rl_clear_history();
	return (0);
}
