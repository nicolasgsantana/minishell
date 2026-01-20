/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nde-sant <nde-sant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/12 10:47:26 by nde-sant          #+#    #+#             */
/*   Updated: 2026/01/20 14:15:00 by nde-sant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

# include "libft.h"

typedef enum e_tk_type
{
	TK_EOF = 0,
	TK_WORD,
	TK_OPERATOR,
}	t_tk_type;

typedef enum e_lx_state
{
	LX_DEFAULT = 0,
	LX_QUOTE,
}	t_lx_state;

typedef enum e_exp
{
	EXP_NONE = 0,
	EXP_DQUOTED,
	EXP_SQUOTED,
}	t_exp;

typedef struct s_token
{
	t_tk_type	type;
	char		*text;
	t_exp		expansion;
}				t_token;

typedef struct s_lexer
{
	char		*line;
	size_t			cursor;
	size_t			line_len;
	t_lx_state		state;
}					t_lexer;

t_lexer	lexer_new(char *line);
t_token	*lexer_next(t_lexer *lexer);
t_token	*new_token(t_tk_type type, char *ref, size_t txt_len, t_exp exp);
int		ft_isspace(int c);

#endif
