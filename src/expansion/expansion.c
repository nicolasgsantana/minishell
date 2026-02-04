/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nde-sant <nde-sant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/03 15:15:46 by nde-sant          #+#    #+#             */
/*   Updated: 2026/02/04 15:55:32 by nde-sant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

char	*strip_quotes(char *text)
{
	return(ft_substr(text, 1, ft_strlen(text) - 2));
}

int	var_start(char *text)
{
	return (*text == '$' && (ft_isalpha(*(text + 1)) || *(text + 1) == '_'));
}

char	*expand(t_token *token, t_shell *sh)
{
	char	*new_text;
	int		i;
	size_t	len;

	(void)new_text;
	if (token->expansion == EXP_SQUOTED)
		return (strip_quotes(token->text));
	i = 0;
	len = 0;
	while (token->text[i])
	{
		if (var_start(&token->text[i]))
		{
			char	*var_value = get_var(&token->text[i], sh->envp);
			ft_printf("%s\n", var_value);
		}
		len++;
		i++;
	}
	return(NULL);
}
