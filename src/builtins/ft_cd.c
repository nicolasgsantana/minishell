/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kqueiroz <kqueiroz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/21 10:30:06 by kqueiroz          #+#    #+#             */
/*   Updated: 2026/02/10 17:50:38 by kqueiroz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*check_cd_args(t_cmd *cmd, t_shell *sh, int *print_pwd)
{
	char	*path;

	if (cmd->argv[2])
	{
		ft_putstr_fd("minishell: cd: too many arguments\n", STDERR_FILENO);
		return (NULL);
	}
	if (cmd->argv[1] && !ft_strncmp(cmd->argv[1], "-", 2))
	{
		*print_pwd = 1;
		path = get_var("$OLDPWD", sh);
		if (!path)
		{
			ft_putstr_fd("minishell: cd: OLDPWD not defined\n", STDERR_FILENO);
			return (NULL);
		}
		return (path);
	}
	if (!cmd->argv[1] || !ft_strncmp(cmd->argv[1], "--", 3))
	{
		path = get_var("$HOME", sh);
		return (path);
	}
	return (ft_strdup(cmd->argv[1]));
}

int	ft_cd(t_shell *sh, t_cmd *cmd)
{
	char	*path;
	char	cwd[1024];
	char	oldpwd[1024];
	int		print_pwd;

	print_pwd = 0;
	if (!getcwd(oldpwd, sizeof(oldpwd)))
		oldpwd[0] = '\0';
	path = check_cd_args(cmd, sh, &print_pwd);
	if (!path)
		return (1);
	if (chdir(path) == -1)
	{
		perror("cd");
		free(path);
		return (1);
	}
	if (oldpwd[0])
		update_env(sh->envp, "OLDPWD", oldpwd);
	if (getcwd(cwd, sizeof(cwd)))
	{
		update_env(sh->envp, "PWD", cwd);
		if (print_pwd)
			ft_putendl_fd(cwd, STDOUT_FILENO);
	}
	free(path);
	return (0);
}
