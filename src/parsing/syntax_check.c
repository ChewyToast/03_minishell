/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_check.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aitoraudicana <aitoraudicana@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 19:09:58 by bmoll-pe          #+#    #+#             */
/*   Updated: 2023/01/15 17:36:19 by aitoraudica      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bmlib.h"
#include "structs.h"
#include "minishell.h"

static _Bool	operator_case(char **input);
static _Bool	bracket_case(char **input);

_Bool	syntax_check(char *input)
{
	int		oper;
	oper = 0;
	if (get_operator(input))
		return (1);
	while(*input)
	{
		oper = get_operator(input);
		oper += extra_operator(input);
		if (oper)
		{
			if (oper > 2)
				input += 1;
			input++;
			if (operator_case(&input))
				return (1);
		}
		else if (*input == '(' && !isscaped(input))
		{
			if (bracket_case(&input))
				return (1);
		}
		else
			input++;
	}
	return (0);
}

static _Bool	operator_case(char **input)
{
	if (get_operator(*input))
		return (1);
	while (*input && **input && **input == ft_isspace(**input))
	{
		(*input)++;
		if (get_operator(*input))
			return (1);
	}
	if (!(**input))
		return (1);
	return (0);
}

static _Bool	bracket_case(char **input)
{
	char	*tmp;

	tmp = *input + get_close_bracket(*input);
	if (!(*tmp))
		return (1);
	*input += 1;
	while (**input && *input < tmp)
	{
		if (**input && **input != ft_isspace(**input))
			break ;
		(*input)++;
	}
	if (*input == tmp)
		return (1);
	*input = tmp;
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