/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kqueiroz <kqueiroz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/07 11:01:31 by nde-sant          #+#    #+#             */
/*   Updated: 2026/02/20 12:03:58 by kqueiroz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <readline/readline.h>
# include <readline/history.h>
# include <unistd.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <stdlib.h>
# include <stdio.h>
# include <fcntl.h>
# include <signal.h>
# include "libft.h"
# include "lexer.h"
# include "struct.h"
# include "parser.h"

extern volatile sig_atomic_t	g_signal;

char	*hd_filename(int i);
void	cleanup_hd(t_cmd *cmd);
int		is_hd_delim(char *line, t_cmd *cmd, int index);
int		prepare_heredocs(t_cmd *cmd, t_shell *sh);
void	child_process(int i, t_shell *sh, int *pipes);
int		wait_for_children(int cmd_count);
int		*create_pipes(int cmd_count);
void	setup_pipes(int i, int cmd_count, int *pipes);
void	close_all_pipes(int *pipes, int cmd_count);
void	execute_cmd(t_cmd *cmd, t_shell *sh);
void	executor(t_shell *sh);
int		ft_cd(t_shell *sh, t_cmd *cmd);
int		ft_echo(t_cmd *cmd);
int		ft_env(t_shell *sh);
int		ft_exit(t_shell *sh, t_cmd *cmd);
int		ft_export(t_shell *sh, t_cmd *cmd);
int		ft_pwd(void);
int		ft_unset(t_shell *sh, t_cmd *cmd);
void	print_env(char **envp);
void	sort_env(char **envp);
void	print_export(char **envp);
int		find_env_index(char **envp, char *key);
int		env_len(char **envp);
int		is_valid_identifier(char *str);
int		update_env(char **envp, char *key, char *value);
char	*make_env_var(char *key, char *value);
int		execute_builtin(t_shell *sh, t_cmd *cmd);
int		apply_redir(t_cmd *cmd);
char	**dup_env(char **envp);
void	sig_exit(t_shell *sh);
void	close_all_fds_except_std(void);
void	free_cmd(t_cmd *cmd);
void	free_sh(t_shell *sh);
void	setup_signals(void);
void	setup_signals_child(void);
int		hd_sigint(char *line, struct sigaction *old_sig);
void	setup_heredoc_signal(struct sigaction *old);
void	warning_hd(t_cmd *cmd, int index);
void	restore_heredoc_signal(struct sigaction *old);
void	clean_otz(char *filename);
int		is_line_whitespace(char *line);

#endif
