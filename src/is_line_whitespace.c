/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_line_whitespace.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nde-sant <nde-sant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/16 13:44:33 by nde-sant          #+#    #+#             */
/*   Updated: 2026/02/16 14:08:39 by nde-sant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_line_whitespace(char *line)
{
	int	i;

	i = 0;
	while (line[i])
		if (!ft_isspace(line[i++]))
			return (0);
	return (1);
}
