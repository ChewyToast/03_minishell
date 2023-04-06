/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmoll-pe <bmoll-pe@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 18:46:17 by ailopez-          #+#    #+#             */
/*   Updated: 2023/04/06 13:00:02 by bmoll-pe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "defines.h"
#include "expander.h"
#include "utils.h"

int	is_literal(t_tokener *tk)
{
	if (tk->is_quoted)
		return (true);
	if (tk->is_dbl_quoted)
		return (true);
	return (false);
}

void	pre_conditions(t_tokener *tk, char *new_data)
{
	if (!tk->is_quoted && !tk->is_dbl_quoted && ft_strlen(new_data) == 0)
		spaces_clean(&tk->data);
	if (tk->exp_mode && tk->data >= tk->end_expansion)
		tk->exp_mode = 0;
}

int	is_isolated_quotes(char	*data, char quote)
{
	if (!ft_isspace(*(data - 1)))
		return (false);
	if (*(data + 1) != quote)
		return (false);
	if (*(data + 2) == '\0')
		return (true);
	if (!ft_isspace(*(data + 2)))
		return (false);
	return (true);
}

bool	is_word_limit(char c, int type)
{
	if (type == LIM_DOLLAR)
	{
		if (!ft_isalnum(c) && c != '_')
			return (true);
		if (c == '/' || c == '$' || c == 39 || c == 34 || c == '\0')
			return (true);
		return (false);
	}
	if (type == LIM_WILDCARD)
	{
		if (c == '>' || c == '<' || c == ' ' || c == '\0')
			return (true);
		return (false);
	}
	if (type == LIM_INIT)
	{
		if (c == '/' || c == '$' || c == 39 || c == 34 || c == '\0')
			return (true);
		if (c == '>' || c == '<' || c == ' ')
			return (true);
		return (false);
	}	
	return (false);
}
