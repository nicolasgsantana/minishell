/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nde-sant <nde-sant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/21 13:50:04 by nde-sant          #+#    #+#             */
/*   Updated: 2026/01/21 13:50:24 by nde-sant         ###   ########.fr       */
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
