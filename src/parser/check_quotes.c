/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_quotes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nde-sant <nde-sant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/27 13:52:21 by nde-sant          #+#    #+#             */
/*   Updated: 2026/02/20 15:32:15 by nde-sant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static void	toggle_quote_status(int *quote_count, int *flag)
{
	*flag = !*flag;
	*quote_count += 1;
}

static int	check_qt_count(t_token *token)
{
	int	quote_count;
	int	i;
	int	inside_dquote;
	int	inside_squote;

	quote_count = 0;
	inside_dquote = 0;
	inside_squote = 0;
	i = 0;
	while (token->text[i])
	{
		if (token->text[i] == '\'' && !inside_dquote)
			toggle_quote_status(&quote_count, &inside_squote);
		else if (token->text[i] == '"' && !inside_squote)
			toggle_quote_status(&quote_count, &inside_dquote);
		i++;
	}
	if (quote_count % 2)
		return (1);
	return (0);
}

int	check_quotes(t_list	*tokens)
{
	t_token	*token;

	while (tokens)
	{
		token = tokens->content;
		if (token->type == TK_WORD)
		{
			if (check_qt_count(token))
			{
				ft_putstr_fd(QT_ERR, STDERR_FILENO);
				return (1);
			}
		}
		tokens = tokens->next;
	}
	return (0);
}
