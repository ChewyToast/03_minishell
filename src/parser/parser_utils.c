/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ailopez- <ailopez-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 19:08:29 by bmoll-pe          #+#    #+#             */
/*   Updated: 2023/03/01 17:36:00 by ailopez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "defines.h"
#include "utils.h"

void	set_top(t_node *node, t_node *top)
{
	while (node)
	{
		node->top = top;
		node = node->next;
	}
}

int	get_operator(char *str)
{
	if (!*str)
		return (TEND);
	if (*str == '|' && *(str + 1) && *(str + 1) == '|'
		&& !isscaped(str))
		return (TOR);
	if (*str == '&' && *(str + 1) && *(str + 1) == '&'
		&& !isscaped(str))
		return (TAND);
	if (*str == '|' && (!*(str + 1) || *(str + 1) != '|')
		&& !isscaped(str))
		return (TPIP);
	return (TUNDEF);
}

int	get_close_bracket(char *line)
{
	int	depth;
	int	count;

	count = 0;
	depth = 0;
	while (line[count])
	{
		if (line[count] == '(' && !isscaped(line))
			depth++;
		if (line[count] == ')' && !isscaped(line))
			depth--;
		if (depth == 0)
			return (count);
		count++;
	}
	return (count);
}