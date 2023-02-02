/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmoll-pe <bmoll-pe@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 00:24:43 by bmoll-pe          #+#    #+#             */
/*   Updated: 2022/06/12 11:47:15 by bmoll-pe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "ft_printf.h"

ssize_t	ft_putstr(const char *str)
{
	ssize_t	size;
	ssize_t	tmp;

	size = 0;
	if (!str)
		return (ft_putstr("(null)"));
	while (str && *str)
	{
		tmp = ft_putchar(*str);
		if (tmp < 0)
			return (-1);
		str++;
		size += tmp;
	}
	return (size);
}
