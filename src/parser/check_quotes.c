/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_quotes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nde-sant <nde-sant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/27 13:52:21 by nde-sant          #+#    #+#             */
/*   Updated: 2026/01/29 09:46:16 by nde-sant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static int	quote_count(t_token *token)
{
	int	count;
	int	i;

	count = 0;
	i = 0;
	while (token->text[i])
	{
		if (token->expansion == EXP_DQUOTED)
			if (token->text[i] == '"')
				count++;
		if (token->expansion == EXP_SQUOTED)
			if (token->text[i] == '\'')
				count++;
		i++;
	}
	return (count);
}

int	check_quotes(t_list	*tokens)
{
	t_token	*token;

	while (tokens)
	{
		token = tokens->content;
		if (token->expansion != EXP_NONE)
		{
			if (quote_count(token) != 2)
			{
				ft_putstr_fd(QT_ERR, STDERR_FILENO);
				return (1);
			}
		}
		tokens = tokens->next;
	}
	return (0);
}
