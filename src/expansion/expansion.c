/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nde-sant <nde-sant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/03 15:15:46 by nde-sant          #+#    #+#             */
/*   Updated: 2026/02/19 19:10:58 by nde-sant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static int	is_var_start(char *str, int i)
{
	return (str[i] == '$' && (valid_var_start(&str[i]) || is_status(&str[i])));
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

static char	*expand_dquoted(char *str, t_shell *sh)
{
	char	*result;
	int		i;

	result = NULL;
	i = 0;
	while (str[i])
	{
		if (is_var_start(str, i))
			result = join_var(str, result, &i, sh);
		else
			result = join_next_char(str[i++], result);
	}
	return (result);
}

static char	*expand_nonquoted(char *str, t_shell *sh, int i)
{
	char	*result;
	int		inside_squote;

	result = NULL;
	inside_squote = 0;
	while (str[i])
	{
		if (str[i] == '\'')
		{
			inside_squote = !inside_squote;
			i++;
		}
		else if (!inside_squote)
		{
			if (str[i] == '"')
				i++;
			else if (is_var_start(str, i))
				result = join_var(str, result, &i, sh);
			else
				result = join_next_char(str[i++], result);
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
	else if (token->expansion == EXP_DQUOTED)
	{
		temp = strip_quotes(token->text);
		new_text = expand_dquoted(temp, sh);
		free(temp);
		return (new_text);
	}
	return (expand_nonquoted(token->text, sh, 0));
}
