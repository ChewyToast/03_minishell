/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmoll-pe <bmoll-pe@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 10:41:50 by bmoll-pe          #+#    #+#             */
/*   Updated: 2022/05/24 22:52:11 by bmoll-pe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

void	ft_putnbr_fd(int n, int fd)
{
	char		c;
	long int	n2;

	n2 = n;
	if (n2 < 0)
	{
		write(fd, "-", 1);
		n2 *= -1;
	}
	if (n2 > 9)
	{
		ft_putnbr_fd(n2 / 10, fd);
		ft_putnbr_fd(n2 % 10, fd);
	}
	else
	{
		c = '0' + n2;
		write(fd, &c, 1);
	}
}
