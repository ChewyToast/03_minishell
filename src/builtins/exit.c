/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: test <test@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 10:39:04 by test              #+#    #+#             */
/*   Updated: 2023/04/04 13:52:13 by test             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "defines.h"
#include "utils.h"
#include "env.h"

static bool	valid_numeric_argv(char *data);
static int	print_exit_error(char *data);

int	exec_exit(t_master *master, t_node *node)
{
	int8_t			value;
	long long		tmp_value;

	value = (int8_t)g_global.num_return_error;
	if (node->tokens[1] && node->tokens[2])
		value = print_error(ft_strdup("exit: too many arguments"), 1, 255);
	else if (node->tokens[1] && !valid_numeric_argv(node->tokens[1]))
		value = print_exit_error(node->tokens[1]);
	else if (node->tokens[1])
	{
		tmp_value = ft_atoi_long_long(node->tokens[1]);
		value = (int8_t)tmp_value;
	}
	free_tree(master->ast);
	env_free_list(master->env_list);
	if (isatty(STDIN_FILENO) && isatty(STDOUT_FILENO))
		if (write(2, "exit\n", 5) < 0)
			exit_program(NULL, 0, 1);
	exit (value);
	return (0);
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
