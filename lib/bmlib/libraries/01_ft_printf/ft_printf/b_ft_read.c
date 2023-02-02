/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_ft_read.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmoll-pe <bmoll-pe@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/12 11:47:47 by bmoll-pe          #+#    #+#             */
/*   Updated: 2022/06/12 11:47:56 by bmoll-pe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "ft_printf.h"

static ssize_t	check_conversion(va_list args, char compare);
static ssize_t	check_bonus(va_list args, const char *str);

ssize_t	ft_read(const char *str, va_list args)
{
	ssize_t	rslt;
	ssize_t	tmp;

	rslt = 0;
	while (*str)
	{
		tmp = 0;
		if (*str == '%')
		{
			if (str[1] != '#')
				tmp = check_conversion(args, *(++str));
			else if (str[1] == '#')
			{
				tmp = check_bonus(args, (++str));
				str++;
			}
		}
		else
			tmp = ft_putchar(*str);
		if (tmp < 0)
			return (-1);
		str++;
		rslt += tmp;
	}
	return (rslt);
}

static ssize_t	check_conversion(va_list args, char compare)
{
	ssize_t	rslt;

	rslt = 0;
	if (compare == 'c')
		rslt = ft_putchar(va_arg(args, int));
	else if (compare == 's')
		rslt = ft_putstr(va_arg(args, char *));
	else if (compare == 'p')
		rslt = ft_ptoa(va_arg(args, unsigned long long int));
	else if (compare == 'd' || compare == 'i')
		rslt = ft_itoa(va_arg(args, int));
	else if (compare == 'u')
		rslt = ft_uitoa(va_arg(args, unsigned int));
	else if (compare == 'x')
		rslt = ft_10to16(va_arg(args, unsigned int), 0);
	else if (compare == 'X')
		rslt = ft_10to16(va_arg(args, unsigned int), 1);
	else if (compare == '%')
		rslt = ft_putchar('%');
	return (rslt);
}

static ssize_t	check_bonus(va_list args, const char *str)
{
	ssize_t	rslt;

	rslt = 0;
	if (*str == '#' && str[1] == 'x')
	{
		rslt = ft_putstr("0x");
		if (rslt < 0)
			return (rslt);
		rslt = ft_10to16(va_arg(args, unsigned int), 0);
	}
	else if (*str == '#' && str[1] == 'X')
	{
		rslt = ft_putstr("0X");
		if (rslt < 0)
			return (rslt);
		rslt = ft_10to16(va_arg(args, unsigned int), 1);
	}
	if (rslt < 0)
		return (rslt);
	return (rslt + 2);
}
