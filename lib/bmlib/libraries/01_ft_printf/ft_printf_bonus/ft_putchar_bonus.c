/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putchar.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmoll-pe <bmoll-pe@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 00:20:18 by bmoll-pe          #+#    #+#             */
/*   Updated: 2022/06/12 11:48:09 by bmoll-pe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "ft_printf_bonus.h"

ssize_t	ft_putcharr(char c)
{
	ssize_t	rslt;

	rslt = write(1, &c, 1);
	if (rslt < 0)
		return (-1);
	return (1);
}
