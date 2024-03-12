/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putdec.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaaraba <aaaraba@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 23:06:29 by aaaraba           #+#    #+#             */
/*   Updated: 2024/03/05 23:06:30 by aaaraba          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static int	ft_lendec(int n)
{
	int	len;

	len = 0;
	if (n == 0)
		len = 1;
	if (n < 0)
	{
		n = n * -1;
		len = 1;
	}
	while (n > 0)
	{
		n = n / 10;
		len++;
	}
	return (len);
}

int	ft_putdec(int n)
{
	int	len;

	len = 0;
	if (n < 0)
		len = 1;
	if (n == -2147483648)
		return (ft_putstr("-2147483648"));
	else if (n < 0)
	{
		ft_putchar('-');
		n = n * -1;
		ft_putdec(n);
	}
	else if (n > 9)
	{
		ft_putdec(n / 10);
		ft_putchar((n % 10) + 48);
	}
	else
	{
		ft_putchar(n + 48);
	}
	return (ft_lendec(n) + len);
}
