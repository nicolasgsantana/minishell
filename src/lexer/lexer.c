/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nde-sant <nde-sant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/14 10:04:33 by nde-sant          #+#    #+#             */
/*   Updated: 2026/01/20 15:31:58 by nde-sant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

t_token	*new_token(t_tk_type type, char *ref, size_t txt_len, t_exp exp)
{
	t_token	*token;
	char	*text;

	token = malloc(sizeof(t_token));
	if (!token)
		return (NULL);
	if (txt_len != 0)
	{
		text = malloc(sizeof(char) * (txt_len + 1));
		ft_strlcpy(text, ref, txt_len + 1);
	}
	else
		text = NULL;
	token->type = type;
	token->text = text;
	token->expansion = exp;
	return (token);
}

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
	lexer->cursor += 1;
	len++;
	while (lexer->line[lexer->cursor] != end_qt && lexer->line[lexer->cursor])
	{
		len++;
		lexer->cursor += 1;
	}
	lexer->cursor += 1;
	len++;
	lexer->state = LX_DEFAULT;
	return (new_token(TK_WORD, ref, len, exp));
}

t_token	*lexer_next(t_lexer *lexer)
{
	if (lexer->state == LX_DEFAULT)
		lexer_trim_left(lexer);
	if (lexer->line[lexer->cursor] == '\'')
		lexer->state = LX_QUOTE;
	else if (lexer->line[lexer->cursor] == '"')
		lexer->state = LX_QUOTE;
	if (lexer->state == LX_QUOTE)
		return (handle_quote(lexer));
	else
		return (new_token(TK_EOF, 0, 0, EXP_NONE));
}
