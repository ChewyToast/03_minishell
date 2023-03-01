/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ailopez- <ailopez-@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 18:46:17 by ailopez-          #+#    #+#             */
/*   Updated: 2023/03/01 18:46:18 by ailopez-         ###   ########.fr       */
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

char	*tknexp_init(char *data, t_tokener *tk, t_master *master, int reset)
{
	if (reset && !data)
		return (NULL);
	if (reset)
	{
		if (tk->original_promt)
			free(tk->original_promt);
		tk->data = ft_strdup(data);
		tk->original_promt = tk->data;
		tk->master = master;
		tk->is_quoted = 0;
		tk->is_dbl_quoted = 0;
		tk->exp_mode = 0;
		tk->end_expansion = NULL;
		tk->return_token = 0;
	}
	tk->full_data = tk->data;
	spaces_clean(&tk->data);
	if (!*tk->data)
	{
		return (NULL);
	}
	return (ft_strdup(""));
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
		if (c == '/')
			return (true);
		if (c == '$')
			return (true);
		if (c == 39)
			return (true);
		if (c == 34)
			return (true);
		if (c == '\0')
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
		if (c == '/')
			return (true);
		if (c == '$')
			return (true);
		if (c == 39)
			return (true);
		if (c == 34)
			return (true);
		if (c == '\0')
			return (true);
		if (c == '>')
			return (true);
		if (c == '<')
			return (true);
		if (c == ' ')
			return (true);
		if (c == '\0')
			return (true);
		return (false);
	}	
	return (false);
}

char	*get_word_end(char *data, int type)
{
	while (*data && !is_word_limit(*data, type))
		data++;
	return (data);
}

char	*get_word_init(char *data, char *data_min, int type)
{
	while (*data && !is_word_limit(*data, type) && data >= data_min)
		data--;
	return (++data);
}
