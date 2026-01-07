/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nde-sant <nde-sant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/07 10:59:11 by nde-sant          #+#    #+#             */
/*   Updated: 2026/01/07 12:17:08 by nde-sant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(void)
{
	char	*line;

	line = "";
	while (line)
	{	
		line = readline("minishell> ");
		if (!line)
			break ;
		if (ft_strlen(line) > 0)
			add_history(line);
		free(line);
	}
	rl_clear_history();
	return (0);
}
