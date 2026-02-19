/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   join_var.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nde-sant <nde-sant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/19 18:54:09 by nde-sant          #+#    #+#             */
/*   Updated: 2026/02/19 18:56:14 by nde-sant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

char	*join_var(char	*str, char *result, int *i, t_shell *sh)
{
	char	*new_result;
	char	*var_name;
	char	*var_value;

	var_name = get_var_name(&str[*i]);
	var_value = get_var(&str[*i], sh);
	if (var_value)
	{
		if (!result)
			new_result = ft_strdup(var_value);
		else
			new_result = ft_strjoin(result, var_value);
		free(result);
	}
	else
		new_result = result;
	*i += ft_strlen(var_name) + 1;
	free(var_name);
	free(var_value);
	return (new_result);
}
