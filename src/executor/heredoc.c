/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kqueiroz <kqueiroz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/02 02:12:19 by kqueiroz          #+#    #+#             */
/*   Updated: 2026/02/13 22:28:01 by kqueiroz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*SIGINT HEREDOC*/

void handle_sigint_heredoc(int sig)
{
	(void)sig;
	g_signal = SIGINT;
	write(STDOUT_FILENO, "\n", 1);
	write(STDERR_FILENO, "DEBUG: SIGINT received\n", 23);
}

void	setup_heredoc_signal(struct sigaction *old)
{
	struct sigaction	new;

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
	ft_putstr_fd(
		"bash: warning: here-document at line 1 delimited by end-of-file (wanted `",
		2);
	ft_putstr_fd(cmd->hd_delim[index], 2);
	ft_putstr_fd("')\n", 2);
}

char	*expand_var(char *line, t_shell *sh, int *i)
{
	int		start;
	char	*var;
	char	*value;

	start = *i;
	(*i)++;
	while (line[*i] && (ft_isalnum(line[*i]) || line[*i] == '_'
			|| line[*i] == '?'))
		(*i)++;
	var = ft_substr(line, start, *i - start);
	value = get_var(var, sh);
	free(var);
	if (!value)
		return (ft_strdup(""));
	return (ft_strdup(value));
}

char	*expand_line(char *line, t_shell *sh)
{
	int		i;
	char	*result;
	char	*new_result;
	char	*tmp;

	i = 0;
	result = ft_strdup("");
	while (line[i])
	{
		if (line[i] == '$' && line[i + 1] != '\0' && line[i + 1] != ' ')
			tmp = expand_var(line, sh, &i);
		else
		{
			tmp = ft_substr(line, i, 1);
			i++;
		}
		new_result = ft_strjoin(result, tmp);
		free(result);
		free(tmp);
		result = new_result;
	}
	return (result);
}

int	read_hd_lines(t_cmd *cmd, int fd, t_shell *sh, int index)
{
	char			*line;
	char			*expanded;
	struct sigaction	old_sig;

	setup_heredoc_signal(&old_sig);
	rl_catch_signals = 0;

	while (1)
	{
		line = readline("> ");

		if (g_signal == SIGINT)
		{
			g_signal = 0;
			if (line)
				free(line);
			rl_catch_signals = 1;
			restore_heredoc_signal(&old_sig);
			return (130);
		}
		if (!line)
		{
			warning_hd(cmd, index);
			break;
		}
		else if (ft_strncmp(line, cmd->hd_delim[index],
				ft_strlen(cmd->hd_delim[index]) + 1) == 0)
		{
			free(line);
			break ;
		}
		else if (!cmd->hd_expand)
		{
			expanded = expand_line(line, sh);
			free(line);
			line = expanded;
		}
		write(fd, line, ft_strlen(line));
		write(fd, "\n", 1);
		free(line);
	}
	rl_catch_signals = 1;
	restore_heredoc_signal(&old_sig);
	return (0);
}

char	*hd_filename(int i)
{
	char	*num;
	char	*tmp;

	num = ft_itoa(i);
	tmp = ft_strjoin("/tmp/.heredoc_", num);
	free(num);
	return (tmp);
}

int	prepare_heredocs(t_cmd *cmd, t_shell *sh)
{
	int		i;
	int		fd;
	int		status;
	char	*filename;

	i = 0;
	while (i < cmd->hd_count)
	{
		filename = hd_filename(i);
		fd = open(filename, O_CREAT | O_WRONLY | O_TRUNC, 0644);
		if (fd < 0)
			return (1);
		status = read_hd_lines(cmd, fd, sh, i);
		close(fd);
		if (status == 130)
		{
			unlink(filename);
			free(filename);
			sh->last_status = 130;
			return (130);
		}
		cmd->input_file = filename;
		i++;
	}
	return (0);
}
