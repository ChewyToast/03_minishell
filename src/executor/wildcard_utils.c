/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ailopez- <ailopez-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 02:49:57 by ailopez-          #+#    #+#             */
/*   Updated: 2023/01/11 03:08:56 by ailopez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "structs.h"
#include "minishell.h"
#include "bmlib.h"

void	step_forward(char **pattern, char **s);

bool	match_wildcard(char *s, char *pattern)
{
	while (*pattern)
	{
		if (*pattern == '*')
		{
			while (*pattern == '*')
				pattern++;
			if (!*pattern)
				return (true);
			while (*s)
			{
				if (match_wildcard(s, pattern))
					return (true);
				s++;
			}
			return (false);
		}
		else if (*pattern == '?')
			step_forward(&pattern, &s);
		else if (*pattern == *s)
			step_forward(&pattern, &s);
		else
			return (false);
	}
	return (!*s);
}

void	step_forward(char **pattern, char **s)
{
	(*pattern)++;
	(*s)++;
}	
