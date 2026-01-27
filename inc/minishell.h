/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keila <keila@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/07 11:01:31 by nde-sant          #+#    #+#             */
/*   Updated: 2026/01/27 19:28:17 by keila            ###   ########.fr       */
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
# include <stdlib.h>
# include "libft.h"

typedef struct s_cmd
{
	char	**argv;
	int		is_builtin;
}	t_cmd;

typedef struct s_shell
{
	t_cmd	*cmds;
	int		cmd_count;
	char	**envp;
	int		last_status;
}	t_shell;

void	child_process(int i, t_shell *sh, int *pipes);
int		wait_for_children(void);
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
int		find_env_index(char **envp, char *key);
int		env_len(char **envp);
int		is_valid_identifier(char *str);
int		update_env(char **envp, char *key, char *value);
char	*make_env_var(char *key, char *value);
int		execute_builtin(t_shell *sh, t_cmd *cmd);

#endif
