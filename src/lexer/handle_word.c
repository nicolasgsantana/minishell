/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_word.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nde-sant <nde-sant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/21 13:54:25 by nde-sant          #+#    #+#             */
/*   Updated: 2026/02/19 20:27:37 by nde-sant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

static void	consume_char(t_lexer *lexer, size_t *len)
{
	*len += 1;
	lexer->cursor += 1;
}

static int	is_valid_char(char c)
{
	return ((!ft_isspace(c) && c) && !starts_with_operator(c));
}

t_token	*handle_word(t_lexer *lexer)
{
	char	*ref;
	size_t	len;

	ref = &lexer->line[lexer->cursor];
	len = 0;
	while (is_valid_char(lexer->line[lexer->cursor]))
		consume_char(lexer, &len);
	return (new_token(TK_WORD, ref, len, EXP_NONE));
}
