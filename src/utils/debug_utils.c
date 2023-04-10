/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmoll-pe <bmoll-pe@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/14 15:19:24 by ailopez-          #+#    #+#             */
/*   Updated: 2023/04/10 13:09:55 by bmoll-pe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "defines.h"
#include "env.h"
#include "utils.h"

char	*node_operator_str(t_node *node)
{
	char	*operator;

	if (node->operator == TEND)
		operator = ft_strdup("END");
	else if (node->operator == TUNDEF)
		operator = ft_strdup("UNDEF");
	else if (node->operator == TPIP)
		operator = ft_strdup("PIPE");
	else if (node->operator == TCOL)
		operator = ft_strdup("COL");
	else if (node->operator == TOR)
		operator = ft_strdup("OR");
	else if (node->operator == TAND)
		operator = ft_strdup("AND");
	else
		operator = ft_strdup("----");
	return (operator);
}

int	is_numeric(char *inp)
{
	while (*inp && ft_isspace(*inp))
		inp++;
	if (!*inp)
		return (0);
	if ((*inp == '-' || *inp == '+') && !(*(inp + 1)))
		return (0);
	if (*inp == '-' || *inp == '+')
		inp++;
	while (*inp && ft_isdigit(*inp))
		inp++;
	while (*inp && ft_isspace(*inp))
		inp++;
	if (*inp)
		return (0);
	return (1);
}

char	*total_trim(char *data, char c)
{
	char	*new_data;

	spaces_clean(&data);
	new_data = ft_strdup("");
	while (*data)
	{
		while ((*data != c && *data) && new_data)
			new_data = ft_chrjoin(new_data, *(data++));
		spaces_clean(&data);
		if (!*data)
			break ;
		data--;
		new_data = ft_chrjoin(new_data, *(data++));
	}
	return (new_data);
}
