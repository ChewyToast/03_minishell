/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_utils2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmoll-pe <bmoll-pe@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 12:59:57 by bmoll-pe          #+#    #+#             */
/*   Updated: 2023/04/06 13:55:43 by bmoll-pe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>
#include "defines.h"

bool	is_word_limit(char c, int type);

int	ft_strcmp(const char *s1, const char *s2)
{
	while (*s1 && *s2 && *s1 == *s2)
	{
		s1++;
		s2++;
	}
	return ((unsigned char)*s1 - (unsigned char)*s2);
}

int	spaces_clean(char **data)
{
	char	*data_in;

	data_in = *data;
	while (ft_isspace(**data) && **data != '\0')
		(*data)++;
	if (ft_isspace(**data))
		(*data)++;
	return (*data - data_in);
}

int	isscaped(char *str)
{
	size_t	count;

	count = 0;
	if (*(str - 1))
		str--;
	else
		return (0);
	while (*(str - count) && *(str - count) == 92)
		count++;
	if (count % 2)
		return (*(str + 1));
	return (0);
}

int	isquote(char *str, char quote)
{
	if (!str || !*str)
		return (0);
	if (*str != quote)
		return (0);
	if (!isscaped(str))
		return (*str);
	return (0);
}

char	*get_word_end(char *data, int type)
{
	while (*data && !is_word_limit(*data, type))
		data++;
	return (data);
}
