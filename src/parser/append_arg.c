/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   append_arg.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nde-sant <nde-sant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/11 17:54:01 by nde-sant          #+#    #+#             */
/*   Updated: 2026/02/11 17:54:35 by nde-sant         ###   ########.fr       */
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
	temp[i++] = ft_strdup(new_arg);
	temp[i] = NULL;
	free_argv(cmd->argv);
	cmd->argv = temp;
}
