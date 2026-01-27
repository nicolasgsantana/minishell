/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_operator.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nde-sant <nde-sant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/21 13:44:35 by nde-sant          #+#    #+#             */
/*   Updated: 2026/01/21 13:53:33 by nde-sant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

int	starts_with_operator(char c)
{
	return (c == '>' || c == '<' || c == '|');
}

t_token	*handle_operator(t_lexer *lexer)
{
	char	*ref;

	ref = &lexer->line[lexer->cursor];
	if (!ft_strncmp(ref, ">>", 2))
	{
		lexer->cursor += 2;
		return (new_token(TK_AP_OUT, ref, 2, EXP_NONE));
	}
	else if (!ft_strncmp(ref, "<<", 2))
	{
		lexer->cursor += 2;
		return (new_token(TK_HEREDOC, ref, 2, EXP_NONE));
	}
	lexer->cursor += 1;
	if (!ft_strncmp(ref, ">", 1))
		return (new_token(TK_RD_OUT, ref, 1, EXP_NONE));
	else if (!ft_strncmp(ref, "<", 1))
		return (new_token(TK_RD_IN, ref, 1, EXP_NONE));
	else
		return (new_token(TK_PIPE, ref, 1, EXP_NONE));
}
