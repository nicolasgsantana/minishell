/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tk_handlers.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nde-sant <nde-sant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/12 20:09:03 by nde-sant          #+#    #+#             */
/*   Updated: 2026/02/12 20:19:42 by nde-sant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
