/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 11:59:35 by marvin            #+#    #+#             */
/*   Updated: 2022/05/23 11:39:33 by bmoll-pe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*str;
	size_t	size;

	size = ft_strlen(s);
	if (!*s || size < start)
		return (ft_calloc(sizeof(char), 1));
	if ((len + start) > size)
		len = size - start;
	str = malloc(sizeof(char) * (len + 1));
	if ((!str) || (!s && len))
		return (0);
	ft_strlcpy(str, s + start, (len + 1));
	return (str);
}
