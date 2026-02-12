/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nde-sant <nde-sant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/26 10:14:53 by nde-sant          #+#    #+#             */
/*   Updated: 2026/02/12 16:13:49 by nde-sant         ###   ########.fr       */
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

void	handle_tk_word(t_cmd *cmd, t_token *tk, t_shell *sh)
{
	char	*arg;

	arg = expand(tk, sh);
	if (!cmd->argv)
		cmd->is_builtin = is_builtin(arg);
	append_arg(cmd, arg);
}

int	handle_tk_rd_out(t_cmd *cmd, t_shell *sh, t_list **tks, int ap)
{
	char	*path;
	t_token	*token;

	if (next_is_word(*tks))
	{
		*tks = (*tks)->next;
		token = (*tks)->content;
		path = expand(token, sh);
		if (redir_out_check(path, 1))
		{
			free(path);
			return (1);
		}
		cmd->append_output = ap;
		free(cmd->output_file);
		cmd->output_file = path;
		return (0);
	}
	if (ap)
		ft_putstr_fd(APP_ERR, STDERR_FILENO);
	else
		ft_putstr_fd(RDOUT_ERR, STDERR_FILENO);
	return (1);
}

int	handle_tk_rd_in(t_cmd *cmd, t_shell *sh, t_list **tks)
{
	char	*path;
	t_token	*token;

	if (next_is_word(*tks))
	{
		*tks = (*tks)->next;
		token = (*tks)->content;

		path = expand(token, sh);
		if (redir_in_check(path))
		{
			free(path);
			return (1);
		}
		free(cmd->input_file);
		cmd->input_file = path;
		return (0);
	}
	ft_putstr_fd(RDIN_ERR, STDERR_FILENO);
	return (1);
}

int	handle_tk_heredoc(t_cmd *cmd, t_list **tks)
{
	char	*delim;
	t_token	*token;

	if (next_is_word(*tks))
	{	
		*tks = (*tks)->next;
		token = (*tks)->content;
		if (token->expansion != EXP_NONE)
			delim = strip_quotes(token->text);
		else
			delim = ft_strdup(token->text);
		append_hd_delim(cmd, delim);
		return (0);
	}
	ft_putstr_fd(HD_ERR, STDERR_FILENO);
	return (1);
}

int	handle_tk_pipe(t_cmd **cmd, t_list **tks, t_shell *sh)
{
	t_token	*token;

	*tks = (*tks)->next;
	token = (*tks)->content;
	if (token->type != TK_EOF)
	{
		append_cmd(sh, *cmd);
		*cmd = new_cmd();
		return (0);
	}
	ft_putstr_fd(PIPE_ERR, STDERR_FILENO);
	return (1);
}

int	parse(char *line, t_shell *sh)
{
	t_list	*tokens;
	t_token	*token;
	t_cmd	*cmd;

	tokens = tokenize(line);
	if (check_quotes(tokens))
	{
		free_token_lst(tokens);
		return (1);
	}
	cmd = new_cmd();
	while (tokens)
	{
		token = tokens->content;
		if (token->type == TK_WORD)
			handle_tk_word(cmd, token, sh);
		if (token->type == TK_AP_OUT)
			if (handle_tk_rd_out(cmd, sh, &tokens, 1))
				return (1);
		if (token->type == TK_RD_OUT)
			if (handle_tk_rd_out(cmd, sh, &tokens, 0))
				return (1);
		if (token->type == TK_RD_IN)
			if (handle_tk_rd_in(cmd, sh, &tokens))
				return (1);
		if (token->type == TK_HEREDOC)
			if (handle_tk_heredoc(cmd, &tokens))
				return (1);
		if (token->type == TK_PIPE)
			if (handle_tk_pipe(&cmd, &tokens, sh))
				return (1);
		tokens = tokens->next;
	}
	append_cmd(sh, cmd);
	return (0);
}
