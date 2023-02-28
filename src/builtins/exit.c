/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ailopez- <ailopez-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 10:39:04 by test              #+#    #+#             */
/*   Updated: 2023/02/28 22:25:51 by ailopez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "defines.h"

int	exec_exit(t_master *master, t_node *node)
{
	int	value;

	value = num_return_error;
	if (node->tokens[1] && node->tokens[2])
		return (write(2, "exit\nba.sh: exit: too many arguments\n", 37));
	if (node->tokens[1] && (!is_numeric(node->tokens[1]) || ft_strlen(node->tokens[1]) > 4))
		write(2, "ba.sh: exit: numeric argument required\n", 39);
	else if (node->tokens[1])
	{
		// If n is specified, but its value is not between 0 and 255 inclusively, the exit status is undefined.
		value = ft_atoi(node->tokens[1]);
		if (value > 255 || value < -255)
			value = 1;
		else if (value < 0)
			value = 255 + value;
	}
	free_tree(master->node);
	env_free_list(master->env_list);
	if (write(2, "exit\n", 5) < 5)
		return (1);// ERROR DE FD
	exit (value);
	return (0);
}
