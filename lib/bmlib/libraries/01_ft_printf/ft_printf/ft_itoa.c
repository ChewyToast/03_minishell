/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 11:59:35 by marvin            #+#    #+#             */
/*   Updated: 2022/06/12 11:47:27 by bmoll-pe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "ft_printf.h"

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
		ft_putchar('-');
	}
	while (--size != -1)
	{
		str[size] = (n % 10) + 48;
		n /= 10;
	}
	return (str);
}

ssize_t	ft_itoa(int n)
{
	char		*str;
	ssize_t		size;
	ssize_t		rtrn;

	if (n == 0)
		return (ft_putchar('0'));
	size = sizeofint((long int)n);
	str = malloc(sizeof(char) * (size + 1));
	if (!str)
		return (-1);
	str[size] = '\0';
	rtrn = ft_putstr(itoa_extract((long int)n, str, size));
	free(str);
	if (n < 0)
		return (rtrn + 1);
	return (rtrn);
}
