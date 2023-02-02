/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalnum.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 11:59:35 by marvin            #+#    #+#             */
/*   Updated: 2022/05/12 00:16:00 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	src_counter;
	size_t	dst_counter;
	size_t	return_value;

	src_counter = 0;
	dst_counter = ft_strlen(dst);
	return_value = ft_strlen(src);
	if (size == 0)
		return (return_value);
	else if (size < ft_strlen(dst))
		return_value += size;
	else
	{
		return_value += ft_strlen(dst);
		size -= dst_counter;
		while (size > 1 && src[src_counter] != '\0')
		{
			dst[dst_counter] = src[src_counter];
			src_counter++;
			dst_counter++;
			size--;
		}
	dst[dst_counter] = '\0';
	}
	return (return_value);
}
