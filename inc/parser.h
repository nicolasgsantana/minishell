/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nde-sant <nde-sant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/26 10:06:56 by nde-sant          #+#    #+#             */
/*   Updated: 2026/02/13 19:34:31 by nde-sant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "minishell.h"

# define QT_ERR "minishell: error: open quotes\n"
# define PIPE_ERR "minishell: error: expected token after '|'\n"
# define PIPE_ERR_2 "minishell: error: expected token before '|'\n"
# define HD_ERR "minishell: error: expected delimiter after '<<'\n"
# define RDIN_ERR "minishell: error: expected path after '<'\n"
# define RDOUT_ERR "minishell: error: expected path after '>'\n"
# define APP_ERR "minishell: error: expected path after '>>'\n"

int		check_quotes(t_list	*tokens);
int		parse(char *line, t_shell *sh);
char	*get_var(char *text, t_shell *sh);
char	*get_var_name(char *text);
char	*strip_quotes(char *text);
char	*expand(t_token *token, t_shell *sh);
char	*expand_var_in_string(char *str, t_shell *sh);
int		valid_var_start(char *text);
int		valid_name_char(char c);
int		is_status(char *text);
void	append_arg(t_cmd *cmd, char *new_arg);
void	append_cmd(t_shell *sh, t_cmd *new_cmd);
void	append_hd_delim(t_cmd *cmd, char *new_delim);
int		redir_out_check(char *file, int append);
int		redir_in_check(char *file);
int		next_is_word(t_list *tokens);
int		is_builtin(char *arg);
void	handle_tk_word(t_cmd *cmd, t_token *tk, t_shell *sh);
int		handle_tk_rd_out(t_cmd *cmd, t_shell *sh, t_list **tks, int ap);
int		handle_tk_rd_in(t_cmd *cmd, t_shell *sh, t_list **tks);
int		handle_tk_heredoc(t_cmd *cmd, t_list **tks, t_shell *sh);
int		handle_tk_pipe(t_cmd **cmd, t_list **tks, t_shell *sh);
t_cmd	*new_cmd(void);
int		is_head_tk_pipe(t_list *tokens, t_shell *sh);
int		to_next_pipe(t_list **tks, t_cmd **cmd);

#endif
