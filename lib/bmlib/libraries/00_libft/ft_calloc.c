/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 11:59:35 by marvin            #+#    #+#             */
/*   Updated: 2022/05/25 02:03:34 by bmoll-pe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	unsigned char	*mall;

	if ((nmemb * size) > 0xffffffff)
		return (NULL);
	mall = malloc (size * nmemb);
	if (mall == NULL)
		return (NULL);
	size *= nmemb;
	while (size--)
		mall[size] = 0;
	return (mall);
}
