/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hanlde_quote.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nde-sant <nde-sant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/21 13:50:55 by nde-sant          #+#    #+#             */
/*   Updated: 2026/01/21 13:52:59 by nde-sant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

static void	consume_char(t_lexer *lexer, size_t *len)
{
	*len += 1;
	lexer->cursor += 1;
}

t_token	*handle_quote(t_lexer *lexer)
{
	char	*ref;
	size_t	len;
	t_exp	exp;
	char	end_qt;

	ref = &lexer->line[lexer->cursor];
	end_qt = lexer->line[lexer->cursor];
	len = 0;
	if (end_qt == '"')
		exp = EXP_DQUOTED;
	else
		exp = EXP_SQUOTED;
	consume_char(lexer, &len);
	while (lexer->line[lexer->cursor] != end_qt && lexer->line[lexer->cursor])
		consume_char(lexer, &len);
	consume_char(lexer, &len);
	lexer->state = LX_DEFAULT;
	return (new_token(TK_WORD, ref, len, exp));
}
