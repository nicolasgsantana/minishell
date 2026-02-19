/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kqueiroz <kqueiroz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/21 10:30:06 by kqueiroz          #+#    #+#             */
/*   Updated: 2026/02/19 15:44:55 by kqueiroz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*check_cd_args(t_cmd *cmd, t_shell *sh)
{
	char	*path;

	if (cmd->argv[1] && !ft_strncmp(cmd->argv[1], "-", 2))
	{
		path = get_var("$OLDPWD", sh);
		if (!path)
		{
			ft_putstr_fd("minishell: cd: OLDPWD not defined\n", STDERR_FILENO);
			return (NULL);
		}
		ft_putendl_fd(path, STDOUT_FILENO);
		return (path);
	}
	if (!cmd->argv[1] || !ft_strncmp(cmd->argv[1], "--", 3)
		|| !ft_strncmp(cmd->argv[1], "~", 2))
	{
		path = get_var("$HOME", sh);
		if (!path)
		{
			ft_putstr_fd("minishell: cd: HOME not set\n", STDERR_FILENO);
			return (NULL);
		}
		return (path);
	}
	return (ft_strdup(cmd->argv[1]));
}

int	chdir_path(char *path)
{
	if (!path)
		return (1);
	if (chdir(path))
	{
		free(path);
		perror("minishell: cd");
		return (1);
	}
	return (0);
}

int	ft_cd(t_shell *sh, t_cmd *cmd)
{
	char	*path;
	char	cwd[1024];
	char	oldpwd[1024];

	if (get_argc(cmd->argv) > 2)
	{
		ft_putstr_fd("minishell: cd: too many arguments\n", STDERR_FILENO);
		return (1);
	}
	if (!getcwd(oldpwd, sizeof(oldpwd)))
		oldpwd[0] = '\0';
	path = check_cd_args(cmd, sh);
	if (!path)
		return (1);
	if (chdir_path(path))
		return (1);
	update_env(sh->envp, "OLDPWD", oldpwd);
	if (getcwd(cwd, sizeof(cwd)))
		update_env(sh->envp, "PWD", cwd);
	free(path);
	return (0);
}
