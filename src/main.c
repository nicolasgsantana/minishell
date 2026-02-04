/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nde-sant <nde-sant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/07 10:59:11 by nde-sant          #+#    #+#             */
/*   Updated: 2026/02/04 14:36:00 by nde-sant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(void)
{
	char	*line;
	t_shell	*sh;

	sh = malloc(sizeof(t_shell));
	char	*envp_test[] = {"ELPHELT=VALENTINE", "JONNHY=SILVERHAND", "NAME=NOT FOUND", NULL};
	sh->envp = envp_test;
	sh->last_status = 2077;
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
		}
		free(line);
	}
	rl_clear_history();
	return (0);
}
