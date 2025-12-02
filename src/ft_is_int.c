/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_is_int.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabrsouz <gabrsouz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 11:06:42 by gabrsouz          #+#    #+#             */
/*   Updated: 2025/06/25 16:46:03 by gabrsouz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static void	ft_putnbr_fd(int n, int fd)
{
	char	number;

	if (n == -2147483648)
		write(fd, "-2147483648", 11);
	else
	{
		if (n < 0)
		{
			write(fd, "-", 1);
			n = -n;
		}
		if (n > 9 && n != -2147483648)
			ft_putnbr_fd(n / 10, fd);
		number = n % 10 + '0';
		write(fd, &number, 1);
	}
}

static int	ft_nbrlen(int n)
{
	int	len;

	if (n == 0)
		return (1);
	len = 0;
	if (n < 0)
		len++;
	while (n) 
	{
		n = n / 10;
		len++;
	}
	return (len);
}

int	ft_is_int(int n)
{
	ft_putnbr_fd(n, 1);
	return (ft_nbrlen(n));
}
