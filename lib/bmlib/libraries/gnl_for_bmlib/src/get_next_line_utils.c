/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmoll-pe <bmoll-pe@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/15 11:47:32 by bmoll-pe          #+#    #+#             */
/*   Updated: 2022/06/15 11:47:33 by bmoll-pe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "get_next_line.h"

char	*ft_strjoinn(char *total_buff, char *tmp)
{
	char	*str;
	size_t	i;
	size_t	total_size;
	size_t	tmp_size;

	i = 0;
	if (!total_buff)
	{
		total_buff = nter_malloc(0, 1);
		if (!total_buff)
			return (NULL);
	}
	total_size = ft_strlenne(total_buff);
	tmp_size = ft_strlenne(tmp);
	str = nter_malloc(total_size + tmp_size + 1, 1);
	if (!str)
		return (NULL);
	while (i++ < total_size)
		str[i - 1] = total_buff[i - 1];
	i = 0;
	while (i++ < tmp_size)
		str[total_size + i - 1] = tmp[i - 1];
	str[total_size + i - 1] = '\0';
	free(total_buff);
	return (str);
}

char	*ft_substrr(const char *total_buff, unsigned int start, size_t len)
{
	char	*str;
	size_t	count;
	size_t	len_src;

	if (!total_buff)
		return (NULL);
	len_src = ft_strlenne(total_buff);
	if (len_src < start)
		start = len_src;
	if (len_src - start < len)
		len = len_src - start;
	str = (char *)nter_malloc(sizeof(char), len);
	if (!str)
		return (NULL);
	count = 0;
	while (start + count < len_src && count < len)
	{
		str[count] = total_buff[start + count];
		count++;
	}
	str[count] = '\0';
	return (str);
}

char	*check_char(const char *str, int c)
{
	if (!str)
		return (NULL);
	while (*str != '\0')
	{
		if (*str == (char)c)
			return ((char *)str);
		str++;
	}
	return (NULL);
}

size_t	ft_strlenne(const char *str)
{
	size_t	size;

	size = 0;
	while (str[size] != '\0')
		size++;
	return (size);
}

char	*nter_malloc(size_t nbytes, size_t size)
{
	char	*str;

	str = malloc(sizeof(char) * (nbytes * size) + 1);
	if (!str)
		return (NULL);
	str[0] = '\0';
	return (str);
}
