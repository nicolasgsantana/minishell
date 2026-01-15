/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nde-sant <nde-sant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/14 10:04:33 by nde-sant          #+#    #+#             */
/*   Updated: 2026/01/15 16:52:37 by nde-sant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

t_token	*new_token(t_token_type type, const char *text, size_t text_size)
{
	t_token	*token;

	token = malloc(sizeof(t_token));
	if (!token)
		return (NULL);
	token->type = type;
	token->text = text;
	token->text_len = text_size;
	return (token);
}

t_lexer	lexer_new(const char *line)
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
	if (lexer->state == LX_DEFAULT)
		lexer_trim_left(lexer);
	else if (lexer->state == LX_S_QUOTE)
	{
		const char	*ref;
		size_t		len;
		ref = &lexer->line[lexer->cursor];
		len = 0;
		while (lexer->line[lexer->cursor] != '\'' && lexer->line[lexer->cursor])
		{
			lexer->cursor += 1;
			len++;
		}
		lexer->state = LX_DEFAULT;
		return (new_token(TK_WORD, ref, len));
	}
	if (lexer->line[lexer->cursor] == '\'')
	{
		lexer->cursor += 1;
		lexer->state = LX_S_QUOTE;
		return (new_token(TK_S_QUOTE, &lexer->line[lexer->cursor - 1], 1));
	}
	return NULL;
}
