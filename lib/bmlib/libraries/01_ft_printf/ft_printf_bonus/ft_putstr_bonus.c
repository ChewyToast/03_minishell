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
#include "ft_printf_bonus.h"

ssize_t	ft_putstrr(const char *str)
{
	ssize_t	size;
	ssize_t	tmp;

	size = 0;
	if (!str)
		return (ft_putstrr("(null)"));
	while (str && *str)
	{
		tmp = ft_putcharr(*str);
		if (tmp < 0)
			return (-1);
		str++;
		size += tmp;
	}
	return (size);
}
