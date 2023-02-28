/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmoll-pe <bmoll-pe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 19:08:29 by bmoll-pe          #+#    #+#             */
/*   Updated: 2023/01/26 17:52:51 by bmoll-pe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bmlib.h"
#include "structs.h"
#include "minishell.h"

void	set_top(t_node *node, t_node *top)
{
	while (node)
	{
		node->top = top;
		node = node->next;
	}
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