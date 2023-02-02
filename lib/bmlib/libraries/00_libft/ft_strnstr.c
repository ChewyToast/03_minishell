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

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;
	size_t	j;
	size_t	k;

	j = ft_strlen(little);
	if (!*little || big == little)
		return ((char *)big);
	k = 0;
	while (*big && len > k)
	{
		i = 0;
		while ((big[i] == little[i])
			&& (len > i + k)
			&& (big[i] && little[i]))
			i++;
		if (i == j)
			return ((char *)big);
		big++;
		k++;
	}
	return (0);
}
