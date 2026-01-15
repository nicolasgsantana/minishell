/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nde-sant <nde-sant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/07 10:59:11 by nde-sant          #+#    #+#             */
/*   Updated: 2026/01/15 16:08:08 by nde-sant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*token_name(t_token_type type);

int	main(void)
{
	char	*line;
	t_lexer	lexer;
	t_token	*token;

	line = "";
	while (line)
	{	
		line = readline("minishell> ");
		if (!line)
			break ;
		if (ft_strlen(line) > 0)
		{
			add_history(line);
			lexer = lexer_new(line);
			token = lexer_next(&lexer);
			while (token->type)
			{
				ft_printf("(%s)\n", token_name(token->type));
				token = lexer_next(&lexer);
			}
		}
		free(line);
	}
	rl_clear_history();
	return (0);
}


// !!!DEBUG ONLY REMOVE LATER
char	*token_name(t_token_type type)
{
	switch (type)
	{
		case TK_EOF:
			return "end of file";
		case TK_WORD:
			return "word";
		case TK_OPERATOR:
			return "operator";
		case TK_REDIR_OP:
			return "redir operator";
		case TK_VAR:
			return "var";
		case TK_S_QUOTE:
			return "single quote";
		case TK_D_QUOTE:
			return "double quote";
		default:
			return NULL;
	}
}
