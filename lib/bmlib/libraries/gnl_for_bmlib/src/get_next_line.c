/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmoll-pe <bmoll-pe@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/15 11:47:32 by bmoll-pe          #+#    #+#             */
/*   Updated: 2022/06/15 11:47:33 by bmoll-pe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "get_next_line.h"

char	*get_next_line(int fd)
{
	static char	*total_buff;
	char		*rtrn_buff;

	if (BUFFER_SIZE <= 0 || fd < 0)
		return (NULL);
	if (!total_buff || (total_buff && !(check_char(total_buff, '\n'))))
		total_buff = fd_readd(fd, total_buff);
	if (!total_buff)
		return (NULL);
	rtrn_buff = take_line(total_buff);
	if (!rtrn_buff)
	{
		free(total_buff);
		return (NULL);
	}
	total_buff = cut_static(total_buff);
	return (rtrn_buff);
}

char	*fd_readd(int fd, char *total_buff)
{
	char	*tmp;
	int		chk;

	tmp = nter_malloc(BUFFER_SIZE, 1);
	if (!tmp)
		return (NULL);
	chk = 1;
	while (chk > 0 && !check_char(tmp, '\n'))
	{
		chk = read(fd, tmp, BUFFER_SIZE);
		if (chk > 0)
		{	
			tmp[chk] = '\0';
			total_buff = ft_strjoinn(total_buff, tmp);
		}
	}
	free(tmp);
	if (chk == -1)
	{
		free(total_buff);
		return (NULL);
	}
	return (total_buff);
}

char	*take_line(char *total_buff)
{
	char	*rtrn_buff;
	size_t	size;

	size = 0;
	if (!total_buff[0])
		return (NULL);
	while (total_buff[size] != '\n' && total_buff[size] != '\0')
		size++;
	if (total_buff[size] == '\n')
		rtrn_buff = ft_substrr(total_buff, 0, size + 1);
	else
		rtrn_buff = ft_substrr(total_buff, 0, size);
	return (rtrn_buff);
}

char	*cut_static(char *total_buff)
{
	size_t	indx;
	char	*new_total_buff;

	indx = 0;
	while (total_buff[indx] != '\n' && total_buff[indx] != '\0')
		indx++;
	if (total_buff[indx] == '\n' && total_buff[indx + 1] != '\0')
	{
		indx++;
		new_total_buff = ft_substrr(total_buff, indx,
				(ft_strlenne(total_buff) - indx));
	}
	else
		new_total_buff = NULL;
	free (total_buff);
	if (!new_total_buff)
		return (NULL);
	return (new_total_buff);
}
