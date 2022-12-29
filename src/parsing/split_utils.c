/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bruno <bruno@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 11:37:56 by bmoll-pe          #+#    #+#             */
/*   Updated: 2022/12/02 22:51:18 by bruno            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "structs.h"
#include "minishell.h"
#include "bmlib.h"

static char	*extra_smart_fill(char *input, size_t *count)
{
	size_t	tmp;
	char	*str;

	tmp = 0;
	while (input[*count] && !ft_isspace(input[*count])
		&& !isquote(&input[*count], 34)
		&& !isquote(&input[*count], 39))
		*count += 1;
	str = ft_calloc(sizeof(char), *(count) + 1);
	if (!str)
		return (NULL);
	while (*input && !ft_isspace(*input)
		&& !isquote(input, 34)
		&& !isquote(input, 39))
	{
		if (*input == 92)
			input++;
		str[tmp] = *input;
		input++;
		tmp++;
	}
	return (str);
}

char	*smart_fill(char *input, char delim, size_t *count)
{
	size_t	tmp;
	char	*str;

	tmp = 0;
	if (delim)
	{
		while (input[*count] && !isquote(&input[*count], delim))
			*count += 1;
		str = ft_calloc(sizeof(char), *(count) + 1);
		if (!str)
			return (NULL);
		while (*input && !isquote(input, delim))
		{
			if (*input == 92)
				input++;
			str[tmp] = *input;
			input++;
			tmp++;
		}
	}
	else
		str = extra_smart_fill(input, count);
	return (str);
}
