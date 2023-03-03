/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ailopez- <ailopez-@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 18:44:51 by ailopez-          #+#    #+#             */
/*   Updated: 2023/03/01 18:44:52 by ailopez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "defines.h"
#include "utils.h"


int	exec_echo(t_node *node)
{
	bool	no_new_line;
	int		i;

	no_new_line = 0;
	i = 1;
	while (node->tokens[i] && !ft_strncmp(node->tokens[i], "-n", 2))
	{
		no_new_line = 1;
		i++;
	}
	while(node->tokens[i])
	{
		ft_putstr_fd(node->tokens[i++], 1);
		if (node->tokens[i] && write(1, " ", 1) < 1)
				return (print_error(ft_strjoin("ba.sh: ", strerror(errno)), 1));
	}
	if (!no_new_line && write(1, "\n", 1) < 0)
		return (print_error(ft_strjoin("ba.sh: ", strerror(errno)), 1));
	return (EXIT_SUCCESS);
}