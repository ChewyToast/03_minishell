/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 11:59:35 by marvin            #+#    #+#             */
/*   Updated: 2022/05/26 21:42:45 by bmoll-pe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

static int	sizeofint(long int n)
{
	long int	indx;
	int			size;

	indx = 1;
	size = 0;
	if (n <= 0)
	{
		indx *= 10;
		size++;
		n *= -1;
	}
	while (n >= indx)
	{
		indx *= 10;
		size++;
	}
	size++;
	return (size);
}

static char	*itoa_extract(long int n, char *str, size_t size)
{
	int	i;

	i = size - 2;
	size--;
	if (n < 0)
	{
		n *= -1;
		*str = '-';
		i++;
	}
	while (size)
	{
		str[i] = (n % 10) + 48;
		n /= 10;
		size--;
		i--;
	}
	return (str);
}

char	*ft_itoa(int n)
{
	char			*str;
	long int		size;

	size = sizeofint((long int)n);
	if (n < 0)
		str = (char *)ft_calloc(sizeof(char), size + 1);
	else
		str = (char *)ft_calloc(sizeof(char), size);
	if (!str)
		return (0);
	return (itoa_extract((long int)n, str, size));
}
