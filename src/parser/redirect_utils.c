/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ailopez- <ailopez-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 18:48:10 by ailopez-          #+#    #+#             */
/*   Updated: 2023/03/12 20:14:04 by ailopez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "defines.h"
#include "utils.h"

int	get_type_redirect(char **data)
{
	if (**data == '<')
	{
		(*data)++;
		if (**data == '<')
		{
			(*data)++;
			return (RDOC);
		}
		return (RIN);
	}
	else if (**data == '>')
	{
		(*data)++;
		if (**data == '>')
		{
			(*data)++;
			return (RADD);
		}
		else
			return (ROUT);
	}
	return (0);
}

bool	is_redirect_limit(char c)
{
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

char	*check_quotes(char *data, bool *is_quoted, bool *is_dbl_quoted)
{
	if ((*data) == 39)
	{
		*is_quoted = !*is_quoted;
		data++;
	}
	else if ((*data) == 34)
	{
		*is_dbl_quoted = !*is_dbl_quoted;
		data++;
	}
	if (*data == 39 || *data == 34)
		data = check_quotes(data, is_quoted, is_dbl_quoted);
	return (data);
}

char	*get_redirect_end(char *data)
{
	bool	is_quoted;
	bool	is_dbl_quoted;

	is_quoted = 0;
	is_dbl_quoted = 0;
	spaces_clean(&data);
	while (*data)
	{
		if (*(data) == 92)
		{
			data++;
			if (*data)
				data++;
		}	
		data = check_quotes(data, &is_quoted, &is_dbl_quoted);
		if (is_redirect_limit(*data) && !is_quoted && !is_dbl_quoted)
			return (data);
		data++;
	}
	return (data);
}

char	*get_redirect_start(char *data, char *promt_init)
{
	char	*data_ini;

	data_ini = data;
	data--;
	while (ft_isdigit(*data) && data > promt_init)
		data--;
	if (data == promt_init && ft_isdigit(*data))
		return (promt_init);
	if (*data == ' ')
		return (data + 1);
	return (data_ini);
}
