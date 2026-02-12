/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nde-sant <nde-sant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/26 10:14:53 by nde-sant          #+#    #+#             */
/*   Updated: 2026/02/12 11:23:02 by nde-sant         ###   ########.fr       */
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

int	handle_tk_rd_out(t_cmd *cmd, t_token *tk, t_shell *sh, int append)
{
	char	*path;

	path = expand(tk, sh);
	if (redir_out_check(path, 1))
	{
		free(path);
		return (1);
	}
	cmd->append_output = append;
	free(cmd->output_file);
	cmd->output_file = path;
	return (0);
}

int	handle_tk_rd_in(t_cmd *cmd, t_token *tk, t_shell *sh)
{
	char	*path;

	path = expand(tk, sh);
	if (redir_in_check(path))
	{
		free(path);
		return (1);
	}
	free(cmd->input_file);
	cmd->input_file = path;
	return (0);
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
		{
			handle_tk_word(cmd, token, sh);
		}
		if (token->type == TK_AP_OUT)
		{
			// CHECK IF HAS A TK_WORD AFTER
			if (next_is_word(tokens))
			{
				tokens = tokens->next;
				token = tokens->content;
				if (handle_tk_rd_out(cmd, token, sh, 1))
				{
					free_token_lst(tokens);
					return (1);
				}
			}
		}
		if (token->type == TK_RD_OUT)
		{
			// CHECK IF HAS A TK_WORD AFTER
			if (next_is_word(tokens))
			{
				tokens = tokens->next;
				token = tokens->content;
				if (handle_tk_rd_out(cmd, token, sh, 0))
				{
					free_token_lst(tokens);
					return (1);
				}
			}
		}
		if (token->type == TK_RD_IN)
		{
			// CHECK IF HAS A TK_WORD AFTER
			if (next_is_word(tokens))
			{
				tokens = tokens->next;
				token = tokens->content;
				if (handle_tk_rd_in(cmd, token, sh))
				{
					free_token_lst(tokens);
					return (1);
				}
			}
		}
		if (token->type == TK_HEREDOC)
		{
			if (next_is_word(tokens))
			{
				tokens = tokens->next;
				token = tokens->content;
				char	*delim;
				if (token->expansion != EXP_NONE)
					delim = strip_quotes(token->text);
				else
					delim = ft_strdup(token->text);
				append_hd_delim(cmd, delim);
			}
		}
		if (token->type == TK_PIPE)
		{
			tokens = tokens->next;
			token = tokens->content;
			// CHECK IF HAS A TK AFTER
			if (token->type != TK_EOF)
			{
				// ADD CURRENT COMMAND TO SHELL CMD LIST
				append_cmd(sh, cmd);
				// INIT NEW COMMAND
				cmd = new_cmd();
			}
		}
		tokens = tokens->next;
	}
	append_cmd(sh, cmd);
	return (0);
}
