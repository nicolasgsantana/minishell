/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kqueiroz <kqueiroz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/02 02:12:19 by kqueiroz          #+#    #+#             */
/*   Updated: 2026/02/12 21:25:20 by kqueiroz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	char	*line;
	char	*expanded;

	while (1)
	{
		line = readline("> ");
		if (!line)
			break ;
		if (ft_strncmp(line, cmd->hd_delim[index],
				ft_strlen(cmd->hd_delim[index]) + 1) == 0)
		{
			free(line);
			break ;
		}
		if (!cmd->hd_expand)
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

int	prepare_heredocs(t_cmd *cmd, t_shell *sh)
{
	int		i;
	int		fd;
	char	*filename;

	i = 0;
	while (i < cmd->hd_count)
	{
		filename = hd_filename(i);
		fd = open(filename, O_CREAT | O_WRONLY | O_TRUNC, 0644);
		if (fd < 0)
			return (1);
		read_hd_lines(cmd, fd, sh, i);
		close(fd);
		cmd->input_file = filename;
		i++;
	}
	return (0);
}
