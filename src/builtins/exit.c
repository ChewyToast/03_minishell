/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmoll-pe <bmoll-pe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 10:39:04 by test              #+#    #+#             */
/*   Updated: 2023/03/09 20:44:00 by bmoll-pe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "defines.h"
#include "utils.h"
#include "env.h"

int	exec_exit(t_master *master, t_node *node)
{
	int8_t			value;
	long long	tmp_value;

	value = (int8_t)global.num_return_error;
	if (node->tokens[1] && node->tokens[2])
		return (print_error(ft_strdup("exit: too many arguments"), 1, write(2, "exit\n", 5) - 4));
	if (node->tokens[1] && !is_numeric(node->tokens[1]))
		exit_program(ft_strdup("exit: numeric argument required"), 1, write(2, "exit\n", 5) - 4);
	if ((node->tokens[1] && node->tokens[1][0] == '+' && ft_strncmp(node->tokens[1], "9223372036854775807", 0xffffffff) < 0)
		|| (node->tokens[1] && node->tokens[1][0] == '-' && ft_strncmp(node->tokens[1] + 1, "9223372036854775808", 0xffffffff) < 0))
		exit_program(ft_strdup("exit: numeric argument required"), 1, write(2, "exit\n", 5) - 4);	
	else if (node->tokens[1])
	{
		tmp_value = ft_atoi_long_long(node->tokens[1]);
		value = (int8_t)tmp_value;
	}
	free_tree(master->node);
	env_free_list(master->env_list);
	if (write(2, "exit\n", 5) < 5)
		exit (1);
	exit (value);
	return (0);
}
