/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   append.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nde-sant <nde-sant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/11 17:54:01 by nde-sant          #+#    #+#             */
/*   Updated: 2026/02/13 19:32:12 by nde-sant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	get_argc(char **argv)
{
	int	argc;

	argc = 0;
	if (!argv)
		return (0);
	while (argv[argc])
		argc++;
	return (argc);
}

void	free_argv(char **argv)
{
	int	i;

	if (!argv)
		return ;
	i = 0;
	while (argv[i])
		free(argv[i++]);
	free(argv);
}

void	append_arg(t_cmd *cmd, char *new_arg)
{
	char	**temp;
	int		i;
	int		argc;

	i = 0;
	argc = get_argc(cmd->argv);
	temp = malloc((argc + 2) * sizeof(char *));
	if (!temp)
		return ;
	while (i < argc)
	{
		temp[i] = ft_strdup(cmd->argv[i]);
		i++;
	}
	temp[i++] = new_arg;
	temp[i] = NULL;
	free_argv(cmd->argv);
	cmd->argv = temp;
}

void	append_cmd(t_shell *sh, t_cmd *new_cmd)
{
	t_cmd	**temp;
	int		i;

	temp = sh->cmds;
	sh->cmd_count += 1;
	sh->cmds = malloc(sizeof(t_cmd *) * (sh->cmd_count + 1));
	if (!sh->cmds)
		return ;
	i = 0;
	if (temp)
	{
		while (temp[i])
		{
			sh->cmds[i] = temp[i];
			temp[i] = NULL;
			i++;
		}
	}
	sh->cmds[i++] = new_cmd;
	sh->cmds[i] = NULL;
	free(temp);
}

void	append_hd_delim(t_cmd *cmd, char *new_delim)
{
	int		i;
	char	**temp;

	temp = cmd->hd_delim;
	cmd->hd_count += 1;
	cmd->hd_delim = malloc(sizeof(char *) * (cmd->hd_count + 1));
	if (!cmd->hd_delim)
		return ;
	i = 0;
	if (temp)
	{
		while (temp[i])
		{
			cmd->hd_delim[i] = temp[i];
			temp[i] = NULL;
			i++;
		}
	}
	cmd->hd_delim[i++] = new_delim;
	cmd->hd_delim[i] = NULL;
	free(temp);
}
