/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nde-sant <nde-sant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/09 10:29:24 by nde-sant          #+#    #+#             */
/*   Updated: 2026/02/09 14:08:15 by nde-sant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

int	valid_var_start(char *text)
{
	return (*text == '$' && (ft_isalpha(*(text + 1)) || *(text + 1) == '_'));
}

int	valid_name_char(char c)
{
	return (ft_isalnum(c) || c == '_');
}

int	is_status(char *text)
{
	return (text[0] == '$' && text[1] == '?' && !valid_name_char(text[2]));
}
