/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nde-sant <nde-sant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/03 15:15:46 by nde-sant          #+#    #+#             */
/*   Updated: 2026/02/09 10:33:01 by nde-sant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

char	*strip_quotes(char *text)
{
	return(ft_substr(text, 1, ft_strlen(text) - 2));
}

char	*substitute_string(char *origin, char *from, char *to)
{
	int		i;
	char	*new;
	char	*slice[2];
	char	*temp;

	new = origin;
	i = 0;
	while (new[i])
	{
		if (!ft_strncmp(&new[i], from, ft_strlen(from)))
		{
			slice[0] = ft_substr(new, 0, i);
			slice[1] = ft_substr(new, i + ft_strlen(from) + 1, ft_strlen(new) - (ft_strlen(from) + i + 1));
			temp = new;
			new = ft_strjoin(slice[0], to);
			free(temp);
			temp = new;
			new = ft_strjoin(temp, slice[1]);
			free(temp);
			i += ft_strlen(to);
		}
		i++;
	}
	return (new);
}

char	*expand(t_token *token, t_shell *sh)
{
	char	*new_text;
	int		i;

	if (token->expansion == EXP_SQUOTED)
		return (strip_quotes(token->text));
	if (token->expansion == EXP_DQUOTED)
		new_text = strip_quotes(token->text);
	i = 0;
	while (token->text[i])
	{
		if (valid_var_start(&token->text[i]))
		{
			if (token->expansion == EXP_NONE)
				return (get_var(&token->text[i], sh->envp));
			char	*start_pos;
			int		len;

			start_pos = &token->text[i++];
			len = 0;
			while (valid_name_char(token->text[i]))
			{
				len++;
				i++;
			}
			new_text = substitute_string(new_text, ft_substr(start_pos, 0, len), get_var(start_pos, sh->envp));
			ft_printf("%s\n", new_text);
		}
		i++;
	}
	return(new_text);
}
