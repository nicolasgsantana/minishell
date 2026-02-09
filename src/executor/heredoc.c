/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kqueiroz <kqueiroz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/02 02:12:19 by kqueiroz          #+#    #+#             */
/*   Updated: 2026/02/09 09:11:43 by kqueiroz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*expand_var(char *line, t_shell *sh, int *i)
{
	int		start;
	char	*var;
	char	*value;

	start = *i;
	while (ft_isalnum(line[*i]) || line[*i] == '_')
		(*i)++;
	var = ft_substr(line, start, *i - start);
	value = get_env(var, sh->envp);
	free(var);
	if (!value)
		return (ft_strdup(""));
	return (ft_strdup(value));
}

char	*expand_line(char *line, t_shell *sh)
{
	int		i;
	char	*result;
	char	*tmp;
	char	buf[2];

	i = 0;
	result = ft_strdup("");
	while (line[i])
	{
		if (line[i] == '$')
		{
			i++;
			tmp = expand_var(line, sh, &i);
		}
		else
		{
			buf[0] = line[i++];
			buf[1] = '\0';
			tmp = ft_strdup(buf);
		}
		result = ft_strjoin(result, tmp);
		free(tmp);
	}
	return (result);
}

int	read_hd_lines(t_cmd *cmd, int fd, t_shell *sh)
{
	char	*line;
	char	*expanded;

	while(1)
	{
		line = readline("> ");
		if (!line)
			break ;
		if (ft_strncmp(line, cmd->hd_delim, ft_strlen(cmd->hd_delim) + 1) == 0)
		{
			free(line);
			break ;
		}
		if (cmd->hd_expand)
		{
			expanded = expand_line(line, sh);
			free(line);
			line = expanded;
		}
		write(fd, line, ft_strlen(line));
		write(fd, "\n", 1);
		free(line);
	}
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

int	handle_hd(t_cmd *cmd, int i, t_shell *sh)
{
	int		fd;
	char	*filename;

	filename = hd_filename(i);
	fd = open(filename, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (fd < 0)
		return (1);
	read_hd_lines(cmd, fd, sh);
	close(fd);
	cmd->input_file = filename;
	return (0);
}

int	prepare_heredocs(t_cmd *cmd, t_shell *sh)
{
	int	i;

	i = 0;
	while (i < cmd->hd_count)
	{
		if (handle_hd(cmd, i, sh))
			return (1);
		i++;
	}
	return (0);
}

// call in main/expand?
// implement cleanup