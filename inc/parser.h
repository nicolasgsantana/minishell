/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nde-sant <nde-sant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/26 10:06:56 by nde-sant          #+#    #+#             */
/*   Updated: 2026/02/11 17:54:56 by nde-sant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "minishell.h"

# define QT_ERR "Error: Open quotes\n"

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

#endif
