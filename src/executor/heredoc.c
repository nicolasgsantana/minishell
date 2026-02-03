/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kqueiroz <kqueiroz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/02 02:12:19 by kqueiroz          #+#    #+#             */
/*   Updated: 2026/02/03 13:03:52 by kqueiroz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*hd_filename(int i)
{
	char	*num;
	char	*tmp;

	num = ft_itoa(i);
	tmp = ft_strjoin("/tmp/.heredoc_", num);
	free(num);
	return (tmp);
}

int	open_hd_file(char *filename)
{
	int	fd;

	fd = open(filename, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (fd < 0)
		perror(filename);
	return (fd);
}

int	read_hd_lines(t_cmd *cmd, int fd)
{
	char	*line;

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
		//if (cmd->hd_expand)
		//	call expand function;
		write(fd, line, ft_strlen(line));
		write(fd, "\n", 1);
		free(line);
	}
	return (0);
}

int	handle_hd(t_cmd *cmd, int i)
{
	int		fd;
	char	*filename;

	filename = hd_filename(i);
	fd = open_hd_file(filename);
	if (fd < 0)
		return (1);
	read_hd_lines(cmd, fd);
	close(fd);
	cmd->input_file = filename;
	return (0);
}

int	prepare_heredocs(t_cmd *cmd)
{
	int	i;

	i = 0;
	while (i < cmd->hd_count)
	{
		if (handle_hd(cmd, i))
			return (1);
		i++;
	}
	return (0);
}

// call in main
// implement cleanup