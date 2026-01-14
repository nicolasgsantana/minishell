/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nde-sant <nde-sant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/12 10:47:26 by nde-sant          #+#    #+#             */
/*   Updated: 2026/01/14 10:47:41 by nde-sant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

# include <stddef.h>

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

typedef struct s_token
{
	t_token_type	type;
	const char		*text;
	size_t			text_size;
}					t_token;

#endif
