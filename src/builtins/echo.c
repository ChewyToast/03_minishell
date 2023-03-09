/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmoll-pe <bmoll-pe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 18:44:51 by ailopez-          #+#    #+#             */
/*   Updated: 2023/03/09 18:42:27 by bmoll-pe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "defines.h"
#include "utils.h"


int	exec_echo(t_node *node)
{
	bool	no_new_line;
	int		i;
	int		j;

	no_new_line = 0;
	i = 1;
	while (node->tokens[i] && node->tokens[i][0] == '-' && node->tokens[i][1] == 'n')
	{
		j = 1;
		while(node->tokens[i][j] == 'n')
			j++;
		if (!(node->tokens[i][j] == ' ' || node->tokens[i][j] == '\0'))
			break;
		no_new_line = 1;
		i++;
	}
	while(node->tokens[i])
	{
		ft_putstr_fd(node->tokens[i++], 1);
		if (node->tokens[i] && write(1, " ", 1) < 1)
			return (print_error(NULL, 0, 1));
	}
	if (!no_new_line && write(1, "\n", 1) < 0)
		return (print_error(NULL, 0, 1));
	return (EXIT_SUCCESS);
}
