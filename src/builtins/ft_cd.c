/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keila <keila@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/21 10:30:06 by kqueiroz          #+#    #+#             */
/*   Updated: 2026/01/27 18:10:19 by keila            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_cd(t_shell *sh, t_cmd *cmd)
{
	char	cwd[1024];

	if (!cmd->argv[1])
	{
		printf("missing arg\n");
		return (1);
	}
	if (chdir(cmd->argv[1]) == -1)
	{
		perror("cd");
		return (1);
	}
	if (getcwd(cwd, sizeof(cwd)))
		update_env(sh->envp, "PWD", cwd);
	return (0);
}

//implementar $HOME?