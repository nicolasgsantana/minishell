/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nde-sant <nde-sant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/21 11:27:35 by nde-sant          #+#    #+#             */
/*   Updated: 2025/09/15 10:53:47 by nde-sant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_printf.h"

int	printfchr(va_list *args)
{
	ft_putchar_fd(va_arg(*args, int), STDOUT_FILENO);
	return (1);
}

int	printfstr(va_list *args)
{
	char	*str;
	int		len;

	str = va_arg(*args, char *);
	if (!str)
	{
		ft_putstr_fd("(null)", STDOUT_FILENO);
		len = 6;
	}
	else
	{
		ft_putstr_fd(str, STDOUT_FILENO);
		len = ft_strlen(str);
	}
	return (len);
}

int	printfint(va_list *args, int is_uint)
{
	char	*converted_int;
	int		len;

	if (is_uint)
		converted_int = ft_uitoa(va_arg(*args, unsigned int));
	else
		converted_int = ft_itoa(va_arg(*args, int));
	ft_putstr_fd(converted_int, STDOUT_FILENO);
	len = ft_strlen(converted_int);
	free(converted_int);
	return (len);
}

int	printfhex(va_list *args, int is_uppercase)
{
	char	*hex;
	int		len;

	hex = ft_itohex(va_arg(*args, unsigned int), is_uppercase);
	ft_putstr_fd(hex, STDOUT_FILENO);
	len = ft_strlen(hex);
	free(hex);
	return (len);
}

int	printfptr(va_list *args)
{
	char	*hex;
	int		len;

	hex = ft_ptrtohex(va_arg(*args, void *));
	if (!hex)
	{
		ft_putstr_fd("(nil)", STDOUT_FILENO);
		len = 5;
	}
	else
	{
		ft_putstr_fd("0x", STDOUT_FILENO);
		len = 2;
		ft_putstr_fd(hex, STDOUT_FILENO);
		len += ft_strlen(hex);
	}
	free(hex);
	return (len);
}
