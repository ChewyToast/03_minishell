/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_utils3.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmoll-pe <bmoll-pe@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 13:51:48 by bmoll-pe          #+#    #+#             */
/*   Updated: 2023/04/06 13:56:02 by bmoll-pe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "defines.h"
#include <stdbool.h>

bool	is_word_limit(char c, int type);

char	*get_word_init(char *data, char *data_min, int type)
{
	while (*data && !is_word_limit(*data, type) && data >= data_min)
		data--;
	return (++data);
}

void	str_to_lower(char *str)
{
	if (!str)
		return ;
	while (*str)
	{
		*str = ft_tolower(*str);
		str++;
	}
}

bool	is_especial(char *str)
{
	if (*str != '\\')
		return (false);
	str++;
	if (*str == 't')
		return (true);
	if (*str == 'n')
		return (true);
	if (*str == 'r')
		return (true);
	if (*str == 'v')
		return (true);
	return (false);
}

char	get_special(char c)
{
	if (c == 't')
		return ('\t');
	if (c == 'n')
		return ('\n');
	if (c == 'v')
		return ('\v');
	if (c == 'r')
		return ('\r');
	return (0);
}

bool	is_free_char(t_is is)
{
	if (is.quoted)
		return (false);
	if (is.dbl_quoted)
		return (false);
	if (is.scaped)
		return (false);
	return (true);
}
