/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nde-sant <nde-sant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/12 10:47:26 by nde-sant          #+#    #+#             */
/*   Updated: 2026/01/12 19:23:31 by nde-sant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

# include <stddef.h>

typedef enum e_token_type
{
	TOKEN_EOF = 0,
	TOKEN_WORD,
	TOKEN_OPERATOR,
}	t_token_type;

typedef struct s_token
{
	t_token_type	type;
	const char		*text;
	const size_t	text_size;
}					t_token;

#endif
