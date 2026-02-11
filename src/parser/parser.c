/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nde-sant <nde-sant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/26 10:14:53 by nde-sant          #+#    #+#             */
/*   Updated: 2026/02/11 18:37:13 by nde-sant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*token_name(t_tk_type type);
void	print_tokens(t_list *tokens);

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
			char *arg = expand(token, sh);
			if (!cmd->argv)
				cmd->is_builtin = is_builtin(arg);
			append_arg(cmd, arg);
		}
		if (token->type == TK_AP_OUT)
		{
			// CHECK IF HAS A TK_WORD AFTER
			if (next_is_word(tokens))
			{
				tokens = tokens->next;
				token = tokens->content;
				// CHECK AND EXPAND VAR(S)
				char	*path = expand(token, sh);
				// CHECK IF A FILE WITH THE TK_WORD PATH ALREADY EXIST
				// CREATE FILE IF NOT
				if (redir_out_check(path, 1))
				{
					free_token_lst(tokens);
					free(path);
					return (1);
				}
				// SET APPEND FLAG TO 1
				cmd->append_output = 1;
				// SET OUTPUT TO FILE
				free(cmd->output_file);
				cmd->output_file = path;
			}
		}
		if (token->type == TK_RD_OUT)
		{
			// CHECK IF HAS A TK_WORD AFTER
			if (next_is_word(tokens))
			{
				tokens = tokens->next;
				token = tokens->content;
				// CHECK AND EXPAND VAR(S)
				char	*path = expand(token, sh);
				// CHECK IF A FILE WITH THE TK_WORD PATH ALREADY EXIST
				// CREATE FILE IF NOT
				if (redir_out_check(path, 1))
				{
					free_token_lst(tokens);
					free(path);
					return (1);
				}
				// SET APPEND FLAG TO 0
				cmd->append_output = 0;
				// SET OUTPUT TO FILE
				free(cmd->output_file);
				cmd->output_file = path;
			}
		}
		if (token->type == TK_RD_IN)
		{
			// CHECK IF HAS A TK_WORD AFTER
			if (next_is_word(tokens))
			{
				tokens = tokens->next;
				token = tokens->content;
				// CHECK AND EXPAND VAR(S)
				char	*path = expand(token, sh);
				// CHECK IF FILE EXISTS RETURN ERROR IF NOT
				if (redir_in_check(path))
				{
					free(path);
					free_token_lst(tokens);
					return (1);
				}
				// SET INPUT TO FILE
				free(cmd->input_file);
				cmd->input_file = path;
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

// !!!DEBUG ONLY REMOVE LATER
char	*token_name(t_tk_type type)
{
	switch (type)
	{
		case TK_EOF:
			return "end of file";
		case TK_WORD:
			return "word";
		case TK_PIPE:
			return "pipe";
		case TK_RD_OUT:
			return "rd out";
		case TK_RD_IN:
			return "rd in";
		case TK_AP_OUT:
			return "ap out";
		case TK_HEREDOC:
			return "heredoc";
		default:
			return NULL;
	}
}

void	print_tokens(t_list *tokens)
{
	t_token	*token;

	while (tokens)
	{
		token = tokens->content;
		ft_printf("%s (%s)\n", token->text, token_name(token->type));
		tokens = tokens->next;
	}
}
