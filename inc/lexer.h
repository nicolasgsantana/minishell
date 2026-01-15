/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nde-sant <nde-sant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/12 10:47:26 by nde-sant          #+#    #+#             */
/*   Updated: 2026/01/15 16:09:00 by nde-sant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

# include "libft.h"

typedef enum e_token_type
{
	TK_EOF = 0,
	TK_WORD,
	TK_OPERATOR,
	TK_REDIR_OP,
	TK_VAR,
	TK_S_QUOTE,
	TK_D_QUOTE,
}	t_token_type;

typedef enum e_lexer_state
{
	LX_DEFAULT,
	LX_D_QUOTE,
	LX_S_QUOTE
}	t_lexer_state;

typedef struct s_token
{
	t_token_type	type;
	const char		*text;
	size_t			text_len;
}					t_token;

typedef struct s_lexer
{
	const char		*line;
	size_t			cursor;
	size_t			line_len;
	t_lexer_state	state;
}					t_lexer;

t_lexer	lexer_new(const char *line);
t_token	*lexer_next(t_lexer *lexer);
t_token	*new_token(t_token_type type, const char *text, size_t text_size);
int		ft_isspace(int c);

#endif
