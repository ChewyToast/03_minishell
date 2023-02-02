/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 11:59:35 by marvin            #+#    #+#             */
/*   Updated: 2022/09/26 15:08:27 by bmoll-pe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "ft_printf_bonus.h"

static ssize_t	sizeofint(long int n)
{
	ssize_t	size;

	size = 0;
	if (n < 0)
		n *= -1;
	while (n > 0)
	{
		n /= 10;
		size++;
	}
	return (size);
}

static char	*itoa_extract(long int n, char *str, ssize_t size)
{
	if (n < 0)
	{
		n *= -1;
		ft_putcharr('-');
	}
	while (--size != -1)
	{
		str[size] = (n % 10) + 48;
		n /= 10;
	}
	return (str);
}

static ssize_t	printer(int n, int space, int sign)
{
	if (!sign && space && n >= 0)
		return (ft_putcharr(' '));
	if (sign && n >= 0)
		return (ft_putcharr('+'));
	return (0);
}

ssize_t	ft_itoaa(int n, int space, int sign)
{
	char		*str;
	ssize_t		size;
	ssize_t		rtrn;

	rtrn = printer(n, space, sign);
	if (n == 0)
		return (rtrn + ft_putcharr('0'));
	size = sizeofint((long int)n);
	str = malloc(sizeof(char) * (size + 1));
	if (!str)
		return (-1);
	str[size] = '\0';
	rtrn += ft_putstrr(itoa_extract((long int)n, str, size));
	free(str);
	if (n < 0)
		return (rtrn + 1);
	return (rtrn);
}
