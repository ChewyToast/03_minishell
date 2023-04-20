/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmoll <bmoll@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 10:39:04 by test              #+#    #+#             */
/*   Updated: 2023/04/18 11:54:21 by bmoll            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "defines.h"
#include "utils.h"
#include "env.h"

static bool	valid_numeric_argv(char *data);
static int	print_exit_error(char *data);
static bool	validate_args(t_node *node, uint8_t *value);

int	exec_exit(t_master *master, t_node *node)
{
	uint8_t			value;
	long long		tmp_value;

	value = (uint8_t)g_global.num_return_error;
	if (master->inter_shell && !node->subshell
		&& node->operator != TPIP
		&& (!node->prev || node->prev->operator != TPIP)
		&& !node->top)
		if (write(2, "exit\n", 5) < 0)
			exit_program(NULL, 0, 1);
	if (!validate_args(node, &value) && node->tokens[1])
	{
		tmp_value = ft_atoi_long_long(node->tokens[1]);
		value = (uint8_t)tmp_value;
	}
	g_global.num_return_error = value;
	if (value == 1)
		return (1);
	env_free_list(master->env_list);
	free_tree(master->ast);
	exit (value);
	return (0);
}

static bool	validate_args(t_node *node, uint8_t *value)
{
	size_t	iter;

	iter = 1;
	if (!node->tokens[1])
		return (0);
	while (node->tokens[iter])
	{
		if (iter >= 2)
		{
			print_error(ft_strdup("exit: too many arguments"), 1, 1);
			*value = 1;
			break ;
		}
		if (!valid_numeric_argv(node->tokens[iter]))
		{
			print_exit_error(node->tokens[iter]);
			*value = 255;
			break ;
		}
		iter++;
	}
	if (!node->tokens[iter] && iter == 2)
		return (0);
	return (1);
}

static bool	valid_numeric_argv(char *data)
{
	bool	neg;

	neg = 0;
	if (!is_numeric(data) || *data == 0)
		return (0);
	if (*data == '-')
		neg = 1;
	if (*data == '-' || *data == '+')
		data++;
	while (*data && *(data + 1) && *data == '0')
		data++;
	if (ft_strlen(data) > 19)
		return (0);
	if (ft_strlen(data) < 19)
		return (1);
	if (!neg && ft_strncmp(data, "9223372036854775807", 0xffffffff) <= 0)
		return (1);
	if (neg && ft_strncmp(data, "9223372036854775808", 0xffffffff) <= 0)
		return (1);
	return (0);
}

static int	print_exit_error(char *data)
{
	write(2, "ba.sh: exit: ", 13);
	write(2, data, ft_strlen(data));
	write(2, ": numeric argument required\n", 28);
	return (255);
}
