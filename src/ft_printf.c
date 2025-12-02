/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabrsouz <gabrsouz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 10:45:18 by gabrsouz          #+#    #+#             */
/*   Updated: 2025/06/25 16:46:14 by gabrsouz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static int	ft_len_args(va_list args, char type)
{
	if (type == 'c')
		return (ft_is_char((char)va_arg(args, int)));
	else if (type == 's')
		return (ft_is_str(va_arg(args, char *)));
	else if (type == 'i' || type == 'd')
		return (ft_is_int(va_arg(args, int)));
	else if (type == 'u')
		return (ft_is_unsigned_int(va_arg(args, unsigned int)));
	else if (type == 'x' || type == 'X')
		return (ft_is_hex(va_arg(args, unsigned int), type));
	else if (type == 'p')
		return (ft_is_hex((unsigned long)va_arg(args, void *), type));
	else if (type == '%')
		return (ft_is_percent());
	else
		return (-1);
}

int	ft_printf(const char *type, ...)
{
	int	i;
	int	len;

	len = 0;
	va_list (args);
	i = 0;
	va_start(args, type);
	while (type[i])
	{
		if (type[i] == '%')
		{
			i++;
			len += ft_len_args(args, type[i]);
			i++;
		}
		else 
		{
			write (1, &type[i], 1);
			len++;
			i++;
		}
	}
	va_end(args);
	return (len);
}
