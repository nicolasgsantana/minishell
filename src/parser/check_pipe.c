/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_pipe.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nde-sant <nde-sant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/13 19:33:23 by nde-sant          #+#    #+#             */
/*   Updated: 2026/02/13 20:04:09 by nde-sant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_head_tk_pipe(t_list *tokens, t_shell *sh)
{
	t_token	*token;

	token = tokens->content;
	if (token->type == TK_PIPE)
	{
		sh->last_status = 2;
		free_token_lst(tokens);
		ft_putstr_fd(PIPE_ERR_2, STDERR_FILENO);
		return (1);
	}
	return (0);
}

int	to_next_pipe(t_list **tks, t_cmd **cmd)
{
	t_token	*token;

	free_cmd(*cmd);
	*cmd = NULL;
	*tks = (*tks)->next;
	while (*tks)
	{
		token = (*tks)->content;
		if (token->type == TK_PIPE)
		{
			*cmd = new_cmd();
			return (1);
		}
		*tks = (*tks)->next;
	}
	return (0);
}
