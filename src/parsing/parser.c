/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmoll-pe <bmoll-pe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/13 23:36:42 by bmoll-pe          #+#    #+#             */
/*   Updated: 2022/12/14 05:04:31 by bmoll-pe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bmlib.h"
#include "structs.h"
#include "minishell.h"

char	isfirst(char *first);
int8_t	get_type(char *input);
int		ft_isscaped(char *str);
int		ft_isquote(char *str, char quote);
_Bool	prepare_first(t_node *node, char *input, size_t count);
_Bool	brackets_loop(char *input, size_t *count, char mode, char quote);

_Bool	parser(t_node *node, char *input, size_t len)
{
	size_t	count = 0;

	if (!node || !input)
		return (1);
	while (input[count] && len)
	{
		if (isfirst(&input[count]))
			return (prepare_first(node, input, count));
		else if (input[count] == '(' && !ft_isscaped(&input[count]))
		{
			if (brackets_loop(input, &count, 0, 0))
				return (1);
		}
		else if (ft_isquote(&input[count], 34))
		{
			if (brackets_loop(input, &count, 1, 34))
				return (1);
		}
		else if (ft_isquote(&input[count], 39))
		{
			if (brackets_loop(input, &count, 1, 39))
				return (1);
		}
		len--;
		count++;
	}
	return (0);
}

_Bool	prepare_first(t_node *node, char *input, size_t count)
{
	size_t	par = 0;
	printf("Nodo en pos: |%zu| con char: ->%c<-\n", count, input[count]);
	node->type = get_type(input + count);
	node->start = input;
	if (input[count] != ';')
		par++;
	par++;
	if (init_node(&node->left))
		return (1);
	node->left->top = node;
	if (init_node(&node->right))
		return (1);
	node->right->top = node;
	if (parser(node->left, input, count - 1)
		|| parser(node->right, input + count + par, 0xffffffff))
		return (1);
	return (0);
}

_Bool	brackets_loop(char *input, size_t *count, char mode, char quote)
{
	size_t	par = 0;

	*count += 1;
	if (!mode)
	{
		while (input[*count] && (input[*count] != ')'
			|| ft_isscaped(&input[*count]) || par))
		{
			if (input[*count] == '(' && !ft_isscaped(&input[*count]))
				par++;
			else if (input[*count] == ')'
				&& !ft_isscaped(&input[*count]) && par)
				par--;
			*count += 1;
		}
		if (!input[*count])
		{
			printf("ba.sh: syntax error: unexpected end of file\n");
			return (1);
		}
		return (0);
	}
	while (input[*count] && !ft_isquote(&input[*count], quote))
		*count += 1;
	if (!input[*count])
	{
		printf("bash: unexpected EOF while looking for matching `\"");
		printf("\'\nba.sh: syntax error: unexpected end of file\n");
		return (1);
	}
	return (0);
}

int8_t	get_type(char *input)
{
	if (*input == ';')
		return (TCOLON);
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

int	ft_isquote(char *str, char quote)
{
	if (*str != quote)
		return (0);
	if (!ft_isscaped(str))
		return (*str);
	return (0);
}

char	isfirst(char *first)
{
	if (*first == ';')
		return (*first);
	if (*first == '|' && *(first + 1) == '|')
		return (*first);
	if (*first == '&' && *(first + 1) == '&')
		return (*first);
	return (0);
}

int	ft_isscaped(char *str)
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
