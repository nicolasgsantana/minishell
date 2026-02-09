/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nde-sant <nde-sant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/26 10:14:53 by nde-sant          #+#    #+#             */
/*   Updated: 2026/02/09 12:00:26 by nde-sant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*token_name(t_tk_type type);
void	print_tokens(t_list *tokens);

int	get_argc(char **argv)
{
	int	argc;

	argc = 0;
	while (argv[argc])
		argc++;
	return (argc);
}

void	free_argv(char **argv)
{
	int	i;

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
	temp = malloc((argc + 1) * sizeof(char *));
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

void	parse(char *line, t_shell *sh)
{
	t_list	*tokens;
	t_token	*token;

	tokens = tokenize(line);
	if (check_quotes(tokens))
		return (free_token_lst(tokens));
	while (tokens)
	{
		token = tokens->content;
		if (token->type == TK_WORD)
		{
			ft_printf("%s\n", expand(token, sh));
		}
		if (token->type == TK_AP_OUT)
		{
			// CHECK IF HAS A TK_WORD AFTER
			// CHECK AND EXPAND VAR(S)
			// CHECK IF A FILE WITH THE TK_WORD PATH ALREADY EXIST
			// CREATE FILE IF NOT
			// SET OUTPUT TO FILE
			// SET APPEND FLAG TO 1
		}
		if (token->type == TK_RD_OUT)
		{
			// CHECK IF HAS A TK_WORD AFTER
			// CHECK AND EXPAND VAR(S)
			// CREATE NEW FILE
			// SET OUTPUT TO FILE
			// SET APPEND FLAG TO 0
		}
		if (token->type == TK_RD_IN)
		{
			// CHECK IF HAS A TK_WORD AFTER
			// CHECK AND EXPAND VAR(S)
			// CHECK IF FILE EXISTS RETURN ERROR IF NOT
			// SET INPUT TO FILE
		}
		if (token->type == TK_HEREDOC)
		{
			// TO BE DISCUSSED
		}
		if (token->type == TK_PIPE)
		{
			// CHECK IF HAS A TK_WORD AFTER
			// ADD CURRENT COMMAND TO SHELL CMD LIST
			// INIT NEW COMMAND
		}
		tokens = tokens->next;
	}
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
