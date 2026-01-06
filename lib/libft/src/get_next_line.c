/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nde-sant <nde-sant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/13 10:02:18 by nde-sant          #+#    #+#             */
/*   Updated: 2025/09/15 10:10:12 by nde-sant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "get_next_line.h"

static char	*get_first_line(char *s)
{
	int		line_len;

	line_len = 0;
	while (s[line_len] && s[line_len] != '\n')
		line_len++;
	if (s[line_len] == '\n')
		line_len++;
	return (ft_substr(s, 0, line_len));
}

static ssize_t	read_until_nl(int fd, char **stash)
{
	ssize_t	bytes_read;
	ssize_t	total_bytes_read;
	char	*temp;
	char	*buffer;

	buffer = malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!buffer)
		return (0);
	total_bytes_read = 0;
	bytes_read = read(fd, buffer, BUFFER_SIZE);
	total_bytes_read += bytes_read;
	while (bytes_read > 0)
	{
		buffer[bytes_read] = '\0';
		temp = *stash;
		*stash = ft_strjoin(temp, buffer);
		free(temp);
		if (ft_strchr(buffer, '\n'))
			break ;
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		total_bytes_read += bytes_read;
	}
	free(buffer);
	return (total_bytes_read);
}

static void	*free_stash(char **stash)
{
	if (*stash)
	{
		free(*stash);
		*stash = NULL;
	}
	return (NULL);
}

char	*get_next_line(int fd)
{
	static char	*stash[MAX_FD];
	char		*temp;
	char		*new_line_pos;
	ssize_t		bytes_read;

	if (fd < 0)
		return (NULL);
	if (!stash[fd])
		stash[fd] = ft_strdup("");
	new_line_pos = ft_strchr(stash[fd], '\n');
	bytes_read = read_until_nl(fd, &stash[fd]);
	if (new_line_pos)
	{
		new_line_pos = ft_strchr(stash[fd], '\n');
		temp = stash[fd];
		stash[fd] = ft_strdup(new_line_pos + 1);
		free(temp);
	}
	else if (!new_line_pos && !bytes_read)
		return (free_stash(&stash[fd]));
	if (bytes_read == 0 && !ft_strlen(stash[fd]))
		return (free_stash(&stash[fd]));
	if (bytes_read < 0)
		return (free_stash(&stash[fd]));
	return (get_first_line(stash[fd]));
}
