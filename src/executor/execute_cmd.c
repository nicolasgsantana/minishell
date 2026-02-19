/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kqueiroz <kqueiroz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/14 19:18:45 by kqueiroz          #+#    #+#             */
/*   Updated: 2026/02/19 15:47:36 by kqueiroz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_arr(char **arr)
{
	int	i;

	if (!arr)
		return ;
	i = 0;
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}

char	*join_path(char *dir, char *cmd)
{
	char	*tmp;
	char	*full;

	tmp = ft_strjoin(dir, "/");
	if (!tmp)
		return (NULL);
	full = ft_strjoin(tmp, cmd);
	free(tmp);
	return (full);
}

char	*get_env_path(char *cmd, char **envp, t_shell *sh)
{
	int		i;

	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], "PATH=", 5) == 0)
			return (envp[i] + 5);
		i++;
	}
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(cmd, 2);
	ft_putstr_fd(": No such file or directory\n", 2);
	free_sh(sh);
	exit(126);
}

char	*find_path(char *cmd, char **envp, t_shell *sh)
{
	char	**dirs;
	char	*full;
	char	*path;
	int		i;

	if (ft_strchr(cmd, '/'))
		return (ft_strdup(cmd));
	path = get_env_path(cmd, envp, sh);
	dirs = ft_split(path, ':');
	i = 0;
	while (dirs[i])
	{
		full = join_path(dirs[i], cmd);
		if (access(full, X_OK) == 0)
		{
			free_arr(dirs);
			return (full);
		}
		free(full);
		i++;
	}
	free_arr(dirs);
	return (NULL);
}

void	execute_cmd(t_cmd *cmd, t_shell *sh)
{
	char	*path;

	path = find_path(cmd->argv[0], sh->envp, sh);
	if (!path)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(cmd->argv[0], 2);
		ft_putstr_fd(": command not found\n", 2);
		free_sh(sh);
		exit(127);
	}
	execve(path, cmd->argv, sh->envp);
	free(path);
	ft_putstr_fd("minishell: ", 2);
	perror(cmd->argv[0]);
	exit(127);
}
