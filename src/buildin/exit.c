/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: test <test@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 10:39:04 by test              #+#    #+#             */
/*   Updated: 2023/01/23 11:13:22 by test             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "structs.h"
#include "minishell.h"
#include "bmlib.h"

int	exec_exit(t_master *master, t_node *node)
{
	int	value;

	ft_printf("EXIT!!!\n");
	value = master->last_ret;
	if (node->tokens[1] && node->tokens[2])
		return (write(2, "ba.sh: exit: too many arguments\n", 32));
	if ((node->tokens[1] && !is_numeric(node->tokens[1])))
		write(2, "ba.sh: exit: numeric argument required\n", 39);
	else if (node->tokens[1])
		value = ft_atoi(node->tokens[1]);// hay que transformarlo bien, es un unsig char de 0 a 255
//	y los negativos passan arriba: -1 --> 254
	free_tree(master->node);
	env_free_list(master->env_list);
	exit (value);
	return (0);
}