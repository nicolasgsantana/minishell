/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_sig.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kqueiroz <kqueiroz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/14 12:10:50 by kqueiroz          #+#    #+#             */
/*   Updated: 2026/02/14 13:05:41 by kqueiroz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_sigint_heredoc(int sig)
{
	(void)sig;
	g_signal = SIGINT;
	rl_done = 1;
	write(STDOUT_FILENO, "^C\n", 3);
	write(STDOUT_FILENO, "minishell> ", 12);
}

void	setup_heredoc_signal(struct sigaction *old)
{
	struct sigaction	new;

	ft_bzero(&new, sizeof(new));
	new.sa_handler = handle_sigint_heredoc;
	new.sa_flags = 0;
	sigemptyset(&new.sa_mask);
	sigaction(SIGINT, &new, old);
}

void	restore_heredoc_signal(struct sigaction *old)
{
	sigaction(SIGINT, old, NULL);
}

void	warning_hd(t_cmd *cmd, int index)
{
	ft_putstr_fd("minishell: warning: here-document at line 1 delimited ", 2);
	ft_putstr_fd("by end-of-file (wanted `", 2);
	ft_putstr_fd(cmd->hd_delim[index], 2);
	ft_putstr_fd("')\n", 2);
}

void	clean_otz(char *filename)
{
	unlink(filename);
	free(filename);
}
