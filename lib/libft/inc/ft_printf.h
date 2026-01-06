/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nde-sant <nde-sant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 15:31:25 by nde-sant          #+#    #+#             */
/*   Updated: 2025/09/15 10:54:12 by nde-sant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>

int		printfchr(va_list *args);
int		printfstr(va_list *args);
int		printfint(va_list *args, int is_uint);
int		printfhex(va_list *args, int is_uppercase);
int		printfptr(va_list *args);

#endif
