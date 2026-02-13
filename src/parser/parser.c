/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nde-sant <nde-sant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/26 10:14:53 by nde-sant          #+#    #+#             */
/*   Updated: 2026/02/13 13:03:43 by nde-sant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_cmd	*new_cmd(void)
{
	t_cmd	*new_cmd;

	new_cmd = malloc(sizeof(t_cmd));
	if (!new_cmd)
		return (NULL);
	new_cmd->argv = NULL;
	new_cmd->input_file = NULL;
	new_cmd->output_file = NULL;
	new_cmd->append_output = 0;
	new_cmd->is_builtin = 0;
	new_cmd->hd_delim = NULL;
	new_cmd->hd_expand = 0;
	new_cmd->hd_count = 0;
	return (new_cmd);
}

int	init_tokens(char *line, t_list **tokens)
{
	*tokens = tokenize(line);
	if (check_quotes(*tokens))
	{
		free_token_lst(*tokens);
		return (1);
	}
	return (0);
}

int	handle_tks(t_cmd **cmd, t_shell *sh, t_list **tks)
{
	t_token	*token;

	token = (*tks)->content;
	if (token->type == TK_WORD)
		handle_tk_word(*cmd, token, sh);
	if (token->type == TK_AP_OUT)
		if (handle_tk_rd_out(*cmd, sh, tks, 1))
			return (1);
	if (token->type == TK_RD_OUT)
		if (handle_tk_rd_out(*cmd, sh, tks, 0))
			return (1);
	if (token->type == TK_RD_IN)
		if (handle_tk_rd_in(*cmd, sh, tks))
			return (1);
	if (token->type == TK_HEREDOC)
		if (handle_tk_heredoc(*cmd, tks))
			return (1);
	if (token->type == TK_PIPE)
		if (handle_tk_pipe(cmd, tks, sh))
			return (1);
	return (0);
}

int	is_head_tk_pipe(t_list *tokens)
{
	t_token	*token;

	token = tokens->content;
	if (token->type == TK_PIPE)
	{
		free_token_lst(tokens);
		ft_putstr_fd(PIPE_ERR_2, STDERR_FILENO);
		return(1);
	}
	return (0);
}

int	to_next_pipe(t_list **tks)
{
	t_token	*token;

	token = (*tks)->content;
	while(*tks)
	{
		if (token->type == TK_PIPE)
			return (1);
		*tks = (*tks)->next;
	}
	return (1);
}

int	parse(char *line, t_shell *sh)
{
	t_list	*tokens;
	t_list	*head;
	t_cmd	*cmd;

	if (init_tokens(line, &tokens))
		return (1);
	head = tokens;
	if (is_head_tk_pipe(head))
		return (1);
	cmd = new_cmd();
	while (tokens)
	{
		if (handle_tks(&cmd, sh, &tokens))
		{
			if (to_next_pipe(&tokens))
				continue ;
			free_token_lst(head);
			return (1);
		}
		tokens = tokens->next;
	}
	append_cmd(sh, cmd);
	free_token_lst(head);
	return (0);
}
