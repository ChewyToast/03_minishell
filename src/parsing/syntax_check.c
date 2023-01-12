/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_check.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmoll-pe <bmoll-pe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 19:09:58 by bmoll-pe          #+#    #+#             */
/*   Updated: 2023/01/12 21:19:35 by bmoll-pe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bmlib.h"
#include "structs.h"
#include "minishell.h"

_Bool	syntax_check(char *input)
{
	size_t	iter;
	int		oper;

	iter = 0;
	oper = 0;
	while(*input)
	{
		oper = get_operator(input);
		oper += extra_operator(input);
		if (oper)
		{
			if (oper > 2)
				input += 1;
			input++;
			while (input && *input && *input == ft_isspace(*input))
			{
				if (get_operator(input))
					return (1);
				input++;
				if (get_operator(input))
					return (1);
			}
			if (!(*input))
				return (1);
		}
		else
			input++;
	}
	return (0);
}

char	extra_operator(char *input)
{
	if (*input == '<' && (!*(input + 1) || *(input + 1) != '<') && !isscaped(input))
		return (1);
	else if (*input == '<' && *(input + 1) && *(input + 1) == '<' && !isscaped(input))
		return (3);
	else if (*input == '>' && (!*(input + 1) || *(input + 1) != '>') && !isscaped(input))
		return (1);
	else if (*input == '>' && *(input + 1) && *(input + 1) == '>' && !isscaped(input))
		return (3);
	return (0);
}