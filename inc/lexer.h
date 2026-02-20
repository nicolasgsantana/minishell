/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nde-sant <nde-sant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/12 10:47:26 by nde-sant          #+#    #+#             */
/*   Updated: 2026/02/20 14:34:50 by nde-sant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

# include "libft.h"

typedef enum e_tk_type
{
	TK_EOF = 0,
	TK_WORD,
	TK_PIPE,
	TK_RD_OUT,
	TK_RD_IN,
	TK_AP_OUT,
	TK_HEREDOC
}	t_tk_type;

typedef enum e_lx_state
{
	LX_DEFAULT = 0,
	LX_DQUOTE,
	LX_SQUOTE
}	t_lx_state;

typedef struct s_token
{
	t_tk_type	type;
	char		*text;
}				t_token;

typedef struct s_lexer
{
	char		*line;
	size_t		cursor;
	size_t		line_len;
	t_lx_state	state;
}				t_lexer;

t_lexer	lexer_new(char *line);
t_token	*lexer_next(t_lexer *lexer);
t_token	*new_token(t_tk_type type, char *ref, size_t txt_len);
int		ft_isspace(int c);
int		starts_with_operator(char c);
t_token	*handle_operator(t_lexer *lexer);
t_token	*handle_quote(t_lexer *lexer);
t_token	*handle_word(t_lexer *lexer);
t_list	*tokenize(char *line);
void	free_token_lst(t_list *token_lst);

#endif
