/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nde-sant <nde-sant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/03 15:15:46 by nde-sant          #+#    #+#             */
/*   Updated: 2026/02/09 14:11:08 by nde-sant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static char	*strip_quotes(char *text)
{
	return (ft_substr(text, 1, ft_strlen(text) - 2));
}

static char	*join_next_char(char c, char *result)
{
	char	temp[2];
	char	*new_result;

	temp[0] = c;
	temp[1] = '\0';
	if (!result)
		return (ft_strdup(temp));
	new_result = ft_strjoin(result, temp);
	free(result);
	return (new_result);
}

static char	*join_var(char	*var_value, char *result)
{
	char	*new_result;

	if (!result)
		return (ft_strdup(var_value));
	new_result = ft_strjoin(result, var_value);
	free(result);
	return (new_result);
}

char	*expand_var_in_string(char *str, t_shell *sh)
{
	char	*result;
	char	*var_name;
	char	*var_value;
	int		i;

	result = NULL;
	i = 0;
	while (str[i])
	{
		if (str[i] == '$' && (valid_var_start(&str[i]) || is_status(&str[i])))
		{
			var_name = get_var_name(&str[i]);
			var_value = get_var(&str[i], sh);
			if (var_value)
				result = join_var(var_value, result);
			i += ft_strlen(var_name) + 1;
			free(var_value);
			free(var_name);
		}
		else
			result = join_next_char(str[i++], result);
	}
	return (result);
}

char	*expand(t_token *token, t_shell *sh)
{
	char	*new_text;
	char	*temp;

	if (token->expansion == EXP_SQUOTED)
		return (strip_quotes(token->text));
	if (token->expansion == EXP_DQUOTED)
	{
		temp = strip_quotes(token->text);
		new_text = expand_var_in_string(temp, sh);
		free(temp);
		return (new_text);
	}
	return (expand_var_in_string(token->text, sh));
}
