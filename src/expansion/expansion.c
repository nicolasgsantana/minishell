/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nde-sant <nde-sant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/03 15:15:46 by nde-sant          #+#    #+#             */
/*   Updated: 2026/02/20 15:37:49 by nde-sant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static void	toggle_quote_status(int *index, int *flag)
{
	*flag = !*flag;
	*index += 1;
}

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

static char	*expand_word(char *str, t_shell *sh, int i)
{
	char	*result;
	int		inside_squote;
	int		inside_dquote;

	result = NULL;
	inside_squote = 0;
	inside_dquote = 0;
	while (str[i])
	{
		if (str[i] == '"' && !inside_squote)
			toggle_quote_status(&i, &inside_dquote);
		else if (str[i] == '\'' && !inside_dquote)
			toggle_quote_status(&i, &inside_squote);
		else if (!inside_squote)
		{
			if (is_var_start(str, i))
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
	return (expand_word(token->text, sh, 0));
}
