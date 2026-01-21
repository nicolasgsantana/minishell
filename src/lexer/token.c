/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nde-sant <nde-sant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/21 13:50:04 by nde-sant          #+#    #+#             */
/*   Updated: 2026/01/21 16:23:53 by nde-sant         ###   ########.fr       */
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

static void	free_token(void *token)
{
	t_token	*tk;

	tk = (t_token *)token;
	free(tk->text);
	free(tk);
}

void	free_token_lst(t_list *token_lst)
{
	t_list	*temp;

	ft_lstiter(token_lst, free_token);
	while (token_lst)
	{
		temp = token_lst;
		token_lst = token_lst->next;
		free(temp);
	}
}

t_list	*tokenize(char *line)
{
	t_list	*token_lst;
	t_token	*token;
	t_lexer	lexer;

	lexer = lexer_new(line);
	token = lexer_next(&lexer);
	token_lst = NULL;
	ft_lstadd_back(&token_lst, ft_lstnew((void *)token));
	while (token->type)
	{
		token = lexer_next(&lexer);
		ft_lstadd_back(&token_lst, ft_lstnew((void *)token));
	}
	return (token_lst);
}
