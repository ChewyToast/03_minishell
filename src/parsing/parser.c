/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmoll-pe <bmoll-pe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/13 23:36:42 by bmoll-pe          #+#    #+#             */
/*   Updated: 2022/12/15 23:23:32 by bmoll-pe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bmlib.h"
#include "structs.h"
#include "minishell.h"
#include <unistd.h>

struct s_parse
{
	char	*start;
	char	*end;
	char	*delim;
	int8_t	type;
}	t_parse;

void	ffwd(char *start, char *end, size_t *count);
int		isparlvl(char *start, char *pos);
int8_t	get_type(char *input);
int		isquote(char *str, char quote);
int		isscaped(char *str);
char	isfirstlvl(char *first);

_Bool	parser(t_node *node, char *start, char *end)
{
	size_t	count;

	printf("end: ->%s<-\n", end);
	if (!start)
		return (1);
	if (!end)
		end = start + (ft_strlen(start) - 1);
	count = 0;
	while (start[count] && &start[count] < end)
	{
		ffwd(&start[count], end, &count);
		if (isfirstlvl(&start[count]) && !isscaped(&start[count]))
		{
			node->type = get_type(&start[count]);
			init_node(&node->right, 1);
			init_node(&node->left, 1);
			if (!node->right || !node->left)
				return (1);
			node->right->top = node;
			node->left->top = node;
			if (parser(node->left, start, &start[count - 1])
				|| parser(node->right, &start[count + 2], end))
				return (1);
			return (0);
		}
		if (&start[count] < end)
			count++;
	}
	node->type = TUNDEF;
	node->start = start;
	node->end = end;
	return (0);
}

void	ffwd(char *start, char *end, size_t *count)
{
	if (isquote(&start[*count], 34))
		while (!isquote(&start[*count], 34) && &start[*count] < end)
			*count += 1;
	else if (isquote(&start[*count], 39))
		while (!isquote(&start[*count], 39) && &start[*count] < end)
			*count += 1;
	else if (start[*count] == '(' && !isscaped(&start[*count]))
		while ((start[*count] != ')' || (start[*count] == ')' && !isscaped(&start[*count])
				&& isparlvl(start, &start[*count]))) && &start[*count] < end)
			*count += 1;
}

int isparlvl(char *start, char *pos)
{
	int level;

	level = 0;
	while(start <= pos)	
	{
		if (level == 0 && *start== ')')
			return (-1);
		if (*start == '(')
			level++;
		if (*start == '(')
			level--;
		start++;
	}
	return (level);
}

int8_t	get_type(char *input)
{
	if (*(input + 1))
	{
		if (*input == '|' && *(input + 1) != '|')
			return (TPIP);
		if (*input == '|' && *(input + 1) == '|')
			return (TOR);
		if (*input == '&' && *(input + 1) != '&')
			return (TAND);
	}
	return (TUNDEF);
}

int	isquote(char *str, char quote)
{
	if (*str != quote)
		return (0);
	if (!isscaped(str))
		return (*str);
	return (0);
}

char	isfirstlvl(char *first)
{
	if (!*(first + 1))
		return (0);
	if (*first == '|' && *(first + 1) == '|')
		return (*first);
	if (*first == '&' && *(first + 1) == '&')
		return (*first);
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
