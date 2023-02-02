/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_10to16.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmoll-pe <bmoll-pe@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/12 11:45:54 by bmoll-pe          #+#    #+#             */
/*   Updated: 2022/06/12 11:46:30 by bmoll-pe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_bonus.h"

static ssize_t	sizeofint(unsigned long long int n)
{
	int	size;

	size = 0;
	while (n > 0)
	{
		n /= 16;
		size++;
	}
	return (size);
}

static ssize_t	printer(char *num, int mode, int flag)
{
	if (!mode && flag)
		return (ft_putstrr("0x") + ft_putstrr(num));
	if (mode && flag)
		return (ft_putstrr("0X") + ft_putstrr(num));
	return (ft_putstrr(num));
}

ssize_t	ft_10to16(unsigned int n, int mode, int flag)
{
	ssize_t	size;
	char	*num;

	if (n == 0)
		return (ft_putcharr('0'));
	size = sizeofint(n);
	num = malloc(sizeof(char) * size + 1);
	if (num == NULL)
		return (-1);
	num[size--] = '\0';
	while (n)
	{
		if (!mode)
			num[size--] = ("0123456789abcdef"[n % 16]);
		else
			num[size--] = ("0123456789ABCDEF"[n % 16]);
		n /= 16;
	}
	size = printer(num, mode, flag);
	free(num);
	return (size);
}
