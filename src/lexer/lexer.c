/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nde-sant <nde-sant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/14 10:04:33 by nde-sant          #+#    #+#             */
/*   Updated: 2026/02/20 14:49:03 by nde-sant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

t_lexer	lexer_new(char *line)
{
	t_lexer	lexer;

	lexer.line = line;
	lexer.cursor = 0;
	lexer.line_len = ft_strlen(line);
	lexer.state = LX_DEFAULT;
	return (lexer);
}

void	lexer_trim_left(t_lexer *lexer)
{
	while (ft_isspace(lexer->line[lexer->cursor]))
		lexer->cursor += 1;
}

t_token	*lexer_next(t_lexer *lexer)
{
	lexer_trim_left(lexer);
	if (starts_with_operator(lexer->line[lexer->cursor]))
		return (handle_operator(lexer));
	else if (lexer->line[lexer->cursor])
		return (handle_word(lexer));
	return (new_token(TK_EOF, NULL, 0));
}
