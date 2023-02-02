/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_ft_read_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmoll-pe <bmoll-pe@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/12 11:47:47 by bmoll-pe          #+#    #+#             */
/*   Updated: 2022/10/07 22:15:01 by bmoll-pe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "ft_printf_bonus.h"

static ssize_t	check_conversion(va_list args, const char *str);
static ssize_t	check_bonus(va_list args, const char *str);
static ssize_t	space_case(va_list args, const char *str);
static ssize_t	read_condition(const char *str);

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
			tmp = check_conversion(args, (++str));
			if (tmp > -1)
				str += read_condition(str);
		}
		else
			tmp = ft_putcharr(*str);
		if (tmp < 0)
			return (-1);
		str++;
		rslt += tmp;
	}
	return (rslt);
}

static ssize_t	read_condition(const char *str)
{
	size_t	size;
	size_t	rtrn;

	size = 0;
	rtrn = 0;
	if (*str == ' ' && str[1] > 47 && str[1] < 58)
	{
		str++;
		while (str[size] > 47 && str[size] < 58)
			size++;
		rtrn += size + 1;
	}
	else if ((*str == ' ' && str[1] == '+')
		|| (*str == '+' && str[1] == ' '))
			rtrn += 2;
	else if (*str == '#' || *str == ' ' || *str == '+')
		rtrn += 1;
	return (rtrn);
}

static ssize_t	check_conversion(va_list args, const char *str)
{
	ssize_t	rslt;

	rslt = 0;
	if (*str == 'c')
		rslt = ft_putcharr(va_arg(args, int));
	else if (*str == 's')
		rslt = ft_putstrr(va_arg(args, char *));
	else if (*str == 'p')
		rslt = ft_ptoa(va_arg(args, unsigned long long int));
	else if (*str == 'd' || *str == 'i')
		rslt = ft_itoaa(va_arg(args, int), 0, 0);
	else if (*str == 'u')
		rslt = ft_uitoa(va_arg(args, unsigned int));
	else if (*str == 'x')
		rslt = ft_10to16(va_arg(args, unsigned int), 0, 0);
	else if (*str == 'X')
		rslt = ft_10to16(va_arg(args, unsigned int), 1, 0);
	else if (*str == '%')
		rslt = ft_putcharr('%');
	else if (*str == '#' || *str == ' ' || *str == '+')
		rslt = check_bonus(args, str);
	return (rslt);
}

static ssize_t	check_bonus(va_list args, const char *str)
{
	ssize_t	rslt;

	rslt = 0;
	if (*str == '#')
	{
		str++;
		if (*str == 'x')
			rslt = ft_10to16(va_arg(args, unsigned int), 0, 1);
		else if (*str == 'X')
			rslt = ft_10to16(va_arg(args, unsigned int), 1, 1);
	}
	else if (*str == ' ' && str[1] != '+' && (str[1] == 'd' || str[1] == 'i'))
		rslt = ft_itoaa(va_arg(args, int), 1, 0);
	else if (*str == ' ' && str[1] != '+' && str[1] == 's')
		rslt = ft_putstrr(va_arg(args, char *));
	else if (*str == ' ' && str[1] == '+')
		rslt = ft_itoaa(va_arg(args, int), 1, 1);
	else if (*str == ' ' && str[1] > 47 && str[1] < 58)
		rslt = space_case(args, ++str);
	else if (*str == '+')
		rslt = ft_itoaa(va_arg(args, int), 0, 1);
	return (rslt);
}

static ssize_t	space_case(va_list args, const char *str)
{
	ssize_t	size;
	ssize_t	rtrn;
	int		space_size;

	size = 0;
	while (str[size] > 47 && str[size] < 58)
		size++;
	if (str[size] == 's')
	{
		rtrn = 0;
		space_size = a_conver_i(str);
		while (space_size--)
		{
			if (ft_putstrr(" ") < 0)
				return (-1);
			rtrn++;
		}
		size = ft_putstrr(va_arg(args, char *));
		if (size < 0)
			return (-1);
		return (rtrn + size);
	}
	return (0);
}
