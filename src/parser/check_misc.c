/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_misc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nde-sant <nde-sant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/11 18:36:24 by nde-sant          #+#    #+#             */
/*   Updated: 2026/02/11 18:36:56 by nde-sant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

int	next_is_word(t_list *tokens)
{
	t_token	*next_token;

	next_token = (tokens->next)->content;
	return (next_token->type == TK_WORD);
}

int	is_builtin(char *arg)
{
	if (!ft_strncmp("echo", arg, 4) && ft_strlen(arg) == 4)
		return (1);
	else if (!ft_strncmp("cd", arg, 2) && ft_strlen(arg) == 2)
		return (1);
	else if (!ft_strncmp("pwd", arg, 3) && ft_strlen(arg) == 3)
		return (1);
	else if (!ft_strncmp("export", arg, 6) && ft_strlen(arg) == 6)
		return (1);
	else if (!ft_strncmp("unset", arg, 5) && ft_strlen(arg) == 5)
		return (1);
	else if (!ft_strncmp("env", arg, 3) && ft_strlen(arg) == 3)
		return (1);
	else if (!ft_strncmp("exit", arg, 4) && ft_strlen(arg) == 4)
		return (1);
	else
		return (0);
}
