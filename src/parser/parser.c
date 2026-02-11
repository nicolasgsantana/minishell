/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nde-sant <nde-sant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/26 10:14:53 by nde-sant          #+#    #+#             */
/*   Updated: 2026/02/11 16:10:45 by nde-sant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*token_name(t_tk_type type);
void	print_tokens(t_list *tokens);

int	get_argc(char **argv)
{
	int	argc;

	argc = 0;
	if (!argv)
		return (0);
	while (argv[argc])
		argc++;
	return (argc);
}

void	free_argv(char **argv)
{
	int	i;

	if (!argv)
		return ;
	i = 0;
	while (argv[i])
		free(argv[i++]);
	free(argv);
}

void	append_arg(t_cmd *cmd, char *new_arg)
{
	char	**temp;
	int		i;
	int		argc;

	i = 0;
	argc = get_argc(cmd->argv);
	temp = malloc((argc + 2) * sizeof(char *));
	if (!temp)
		return ;
	while (i < argc)
	{
		temp[i] = ft_strdup(cmd->argv[i]);
		i++;
	}
	temp[i++] = ft_strdup(new_arg);
	temp[i] = NULL;
	free_argv(cmd->argv);
	cmd->argv = temp;
}

//TODO: CHECK HOW TO HANDLE CASE WHEN WORD IS EMPTY
int	next_is_word(t_list *tokens)
{
	t_token	*next_token;

	next_token = (tokens->next)->content;
	return (next_token->type == TK_WORD);
}

int	redir_out_check(char *file, int append)
{
	int	fd;

	if (append)
		fd = open(file, O_WRONLY | O_CREAT | O_APPEND, 0644);
	else
		fd = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd < 0)
	{
		perror("minishell: ");
		return (1);
	}
	close(fd);
	return (0);
}

int	redir_in_check(char *file)
{
	int	fd;

	fd = open(file, O_RDONLY);
	if (fd < 0)
	{
		perror("minishell: ");
		return (1);
	}
	close(fd);
	return (0);
}

t_cmd	*new_cmd(void)
{
	t_cmd	*new_cmd;

	new_cmd = malloc(sizeof(t_cmd));
	if (!new_cmd)
		return (NULL);
	new_cmd->argv = NULL;
	new_cmd->input_file = NULL;
	new_cmd->append_output = 0;
	new_cmd->is_builtin = 0;
	new_cmd->hd_delim = NULL;
	new_cmd->hd_expand = 0;
	new_cmd->hd_count = 0;
	return (new_cmd);
}

void	append_cmd(t_shell *sh, t_cmd *new_cmd)
{
	t_cmd	**temp;
	int		i;

	temp = sh->cmds;
	sh->cmd_count += 1;
	sh->cmds = malloc(sizeof(t_cmd *) * sh->cmd_count + 1);
	if (!sh->cmds)
		return ;
	i = 0;
	if (temp)
	{
		while (temp[i])
		{
			sh->cmds[i] = temp[i];
			temp[i] = NULL;
			i++;
		}
	}
	sh->cmds[i++] = new_cmd;
	sh->cmds[i] = NULL;
	free(temp);
}

void	append_hd_delim(t_cmd *cmd, char *new_delim)
{
	int		i;
	char	**temp;

	temp = cmd->hd_delim;
	cmd->hd_count += 1;
	cmd->hd_delim = malloc(sizeof(char *) * cmd->hd_count + 1);
	if (!cmd->hd_delim)
		return ;
	i = 0;
	while (temp[i])
	{
		cmd->hd_delim[i] = temp[i];
		temp[i] = NULL;
		i++;
	}
	cmd->hd_delim[i++] = new_delim;
	cmd->hd_delim[i] = NULL;
	free(temp);
}

int	is_builtin(char *arg)
{
	if (!ft_strncmp("echo", arg, 4) && ft_strlen(arg) == 4)
		return (1);
	else if (!ft_strncmp("cd", arg, 2) && ft_strlen(arg) == 2)
		return (1);
	else if (!ft_strncmp("pwd", arg, 3) && ft_strlen(arg) == 3)
		return (1);
	else if (!ft_strncmp("export", arg, 6) && ft_strlen(arg) == 6)
		return (1);
	else if (!ft_strncmp("unset", arg, 5) && ft_strlen(arg) == 5)
		return (1);
	else if (!ft_strncmp("env", arg, 3) && ft_strlen(arg) == 3)
		return (1);
	else if (!ft_strncmp("exit", arg, 4) && ft_strlen(arg) == 4)
		return (1);
	else
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
