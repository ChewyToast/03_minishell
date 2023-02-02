/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmoll-pe <bmoll-pe@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/15 11:47:39 by bmoll-pe          #+#    #+#             */
/*   Updated: 2022/06/15 11:47:40 by bmoll-pe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "get_next_line_bonus.h"

char	*ft_strjoinn(char *total_buff, char *tmp, size_t totalln, size_t tmpln)
{
	char	*str;
	size_t	indx;

	indx = 0;
	if (!total_buff)
	{
		total_buff = malloc(sizeof(char *) * 1);
		if (!total_buff)
			return (NULL);
		*total_buff = '\0';
	}
	str = malloc(sizeof(char) * (totalln + tmpln + 1));
	if (!str)
		return (NULL);
	while (indx++ < totalln)
		str[indx - 1] = total_buff[indx - 1];
	indx = 0;
	while (indx++ < tmpln)
		str[totalln + indx - 1] = tmp[indx - 1];
	str[totalln + indx - 1] = '\0';
	free(total_buff);
	return (str);
}

char	*ft_substrr(char *total_buff, size_t start, size_t len)
{
	char	*str;
	size_t	indx;

	indx = 0;
	if (ft_strlenne(total_buff) < start)
		str = malloc(sizeof(char) * 1);
	else if (ft_strlenne(total_buff) - start < len)
		str = malloc(sizeof(char) * (ft_strlenne(total_buff) - start + 1));
	else
		str = (char *)malloc(sizeof(char) * (len + 1));
	if (!str)
		return (NULL);
	while (start + indx < ft_strlenne(total_buff) && indx < len)
	{
		str[indx] = total_buff[start + indx];
		indx++;
	}
	str[indx] = '\0';
	return (str);
}

size_t	check_nl(const char *str)
{
	size_t	size;

	size = 0;
	if (!str)
		return (0);
	while (str[size] && str[size] != '\n')
		size++;
	if (!str[size])
		return (0);
	return (size);
}

size_t	ft_strlenne(const char *s)
{
	size_t	size;

	size = 0;
	if (!s)
		return (0);
	while (s[size] != '\0')
		size++;
	return (size);
}
