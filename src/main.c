/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nde-sant <nde-sant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/07 10:59:11 by nde-sant          #+#    #+#             */
/*   Updated: 2026/01/21 16:19:56 by nde-sant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*token_name(t_tk_type type);

int	main(void)
{
	char	*line;
	t_list	*tokens;

	line = "";
	while (line)
	{	
		line = readline("minishell> ");
		if (!line)
			break ;
		if (ft_strlen(line) > 0)
		{
			add_history(line);
			tokens = tokenize(line);
			free_token_lst(tokens);
		}
		free(line);
	}
	rl_clear_history();
	return (0);
}


// !!!DEBUG ONLY REMOVE LATER
char	*token_name(t_tk_type type)
{
	switch (type)
	{
		case TK_EOF:
			return "end of file";
		case TK_WORD:
			return "word";
		case TK_PIPE:
			return "pipe";
		case TK_RD_OUT:
			return "rd out";
		case TK_RD_IN:
			return "rd in";
		case TK_AP_OUT:
			return "ap out";
		case TK_HEREDOC:
			return "heredoc";
		default:
			return NULL;
	}
}
