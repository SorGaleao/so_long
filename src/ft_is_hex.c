/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_is_hex.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabrsouz <gabrsouz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 10:55:52 by gabrsouz          #+#    #+#             */
/*   Updated: 2025/06/25 16:46:01 by gabrsouz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static int	ft_hexlen(unsigned long n)
{
	unsigned int	len;

	if (n == 0)
		return (1);
	len = 0;
	while (n) 
	{
		n = n / 16;
		len++;
	}
	return (len);
}

static void	ft_putchar_fd(char c, int fd)
{
	write(fd, &c, 1);
}

static void	ft_convert_hex(unsigned long dec, const char type)
{
	char	*hexstr;

	if (type == 'x' || type == 'p')
		hexstr = "0123456789abcdef";
	else if (type == 'X')
		hexstr = "0123456789ABCDEF";
	else
		return ;
	if (dec >= 16)
		ft_convert_hex (dec / 16, type);
	ft_putchar_fd((hexstr[dec % 16]), 1);
}

int	ft_is_hex(unsigned long dec, const char type)
{
	if (type == 'p')
	{
		if (!dec)
			return (write(1, "(nil)", 5));
		write(1, "0x", 2);
		ft_convert_hex (dec, type);
		return (ft_hexlen(dec) + 2);
	}
	ft_convert_hex (dec, type);
	return (ft_hexlen(dec));
}

/*int	main(void)
{
	//printf("\nlen = %d", ft_is_hex(16075, 'x'));
	unsigned int    num = 160;
    unsigned int    num2 = 48879; // 0xBEEF em decimal
    void            *ptr = &num;

    // Testando o tipo 'x'
    printf("Hexadecimal minúsculo: ");
    printf("len = %d\n", ft_is_hex(num, 'x'));

    // Testando o tipo 'X'
    printf("Hexadecimal maiúsculo: ");
    printf("len = %d\n", ft_is_hex(num, 'X'));

    // Testando o tipo 'p' (ponteiro)
    printf("\nEndereço do ponteiro: ");
    ft_is_hex((unsigned long)ptr, 'p');
    printf("\n");

    // Testando com outro número
    printf("Número adicional (BEEF): ");
    printf("len = %d\n", ft_is_hex(num2, 'x'));
	printf("\nlen = %d", ft_is_hex(48879, 'x'));
}*/