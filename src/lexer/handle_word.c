/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_word.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nde-sant <nde-sant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/21 13:54:25 by nde-sant          #+#    #+#             */
/*   Updated: 2026/02/20 14:59:27 by nde-sant         ###   ########.fr       */
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
	return (((!ft_isspace(c) && c) && !starts_with_operator(c)));
}

static void	toggle_squote_state(t_lexer *lexer)
{
	if (lexer->state == LX_SQUOTE)
		lexer->state = LX_DEFAULT;
	else
		lexer->state = LX_SQUOTE;
}

static void	toggle_dquote_state(t_lexer *lexer)
{
	if (lexer->state == LX_DQUOTE)
		lexer->state = LX_DEFAULT;
	else
		lexer->state = LX_DQUOTE;
}

t_token	*handle_word(t_lexer *lexer)
{
	char	*ref;
	size_t	len;

	ref = &lexer->line[lexer->cursor];
	len = 0;
	while (lexer->line[lexer->cursor])
	{
		if (lexer->line[lexer->cursor] == '"' && lexer->state != LX_SQUOTE)
			toggle_dquote_state(lexer);
		if (lexer->line[lexer->cursor] == '\'' && lexer->state != LX_DQUOTE)
			toggle_squote_state(lexer);
		if (lexer->state != LX_DEFAULT)
			consume_char(lexer, &len);
		else
		{
			if (!is_valid_char(lexer->line[lexer->cursor]))
				break ;
			consume_char(lexer, &len);
		}
	}
	return (new_token(TK_WORD, ref, len));
}
