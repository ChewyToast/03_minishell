/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmoll-pe <bmoll-pe@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 12:34:55 by bmoll-pe          #+#    #+#             */
/*   Updated: 2023/04/06 13:46:53 by bmoll-pe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "defines.h"
#include "utils.h"
#include "env.h"
#include "signals.h"
#include "parser.h"
#include "executor.h"
#include <stdlib.h>

static void	print_shlvl_error(int value);

void	default_env(t_master *master)
{
	char	*buff;

	buff = ft_calloc(PATH_MAX + 1, 1);
	if (env_new_value(&master->env_list, "PATH",
			"/usr/gnu/bin:/usr/local/bin:/bin:/usr/bin:."))
		exit_program(NULL, 0, 1);
	if (env_new_value(&master->env_list->next, "SHLVL", "1"))
		exit_program(NULL, 0, 1);
	if (!getcwd(buff, PATH_MAX))
		exit_program(NULL, 0, 1);
	if (env_new_value(&master->env_list->next->next, "PWD", buff))
		exit_program(NULL, 0, 1);
	if (env_new_value(&master->env_list->next->next->next, "_",
			"/usr/bin/env"))
		exit_program(NULL, 0, 1);
	master->tild_value = ft_substr("/Users/userID", 0, 14);
	free(buff);
}

void	bash_lvl_calculator(t_env *node,
				long long_value, unsigned int value)
{
	if (!ft_strncmp("9223372036854775807", node->value, 20))
		value = -1;
	else
	{
		long_value = ft_atoi_long_long(node->value);
		if (long_value == LLONG_MAX)
			value = 0;
		else if (strlen(node->value) > 10)
			value = 0xFFFFFFFF & long_value;
		else
			value = (int)long_value;
	}		
	if (++value > INT_MAX || value < 0)
		value = 0;
	free(node->value);
	if (value > 1000)
	{
		print_shlvl_error(value);
		value = 1;
	}
	if (value == 1000)
		node->value = NULL;
	else
		node->value = ft_itoa(value);
}

static void	print_shlvl_error(int value)
{
	ft_putstr_fd("ba.sh: warning: shell level ", 2);
	ft_putnbr_fd(value, 2);
	ft_putstr_fd(" too high, resetting to 1\n", 2);
}
