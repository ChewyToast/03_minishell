/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envoiroment.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: test <test@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 12:02:19 by test              #+#    #+#             */
/*   Updated: 2023/03/05 13:08:02 by test             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "defines.h"
#include "env.h"
#include "utils.h"
#include "builtin_utils.h"
#include "envoirment_utils.h"

int	exec_env(t_master *master, t_node *node)
{
	size_t	iter;
	char	**print;

	iter = 0;
	if (node->tokens[1])
	print = env_to_array(master->env_list);
	if (!print)
		return (1);//ERROR!@to_do
	while (print[iter])
	{
		if (ft_strchr(print[iter], '=') && write(stdout, print[iter], ft_strlen(print[iter])) < 0)
		{
			free_slpit(print);
			return (1);//ERROR!@to_do
		}
		iter++;
	}
	free_slpit(print);
	return (0);
}

int	exec_export(t_master *master, t_node *node)
{
	char	*name;
	char	*value;
	int8_t	rtrn;

	rtrn = 0;
	if (node->tokens[0] && !node->tokens[1])
		return (print_export(master));
	while (node->tokens[1])
	{
		name = NULL;
		value = NULL;
		if (get_export_values(node, &name, &value))
			return (1);
		ft_printf("NEW values: %s=%s\n", name, value);
		rtrn = set_new_values(master, name, value);
		prepare_next_export(node);
	}
	if (rtrn)
		return (print_error(ft_strdup("ba.sh: Error trying to allocate memory"), 1));
	return (rtrn);
}

int	exec_unset(t_master *master, t_node *node)
{
	char	**tokens;

	tokens = node->tokens;
	tokens += 1;
	while (*(tokens))
		env_unset_node(master, *(tokens++));
	return (0);
}

int	print_export(t_master *master)
{
	char	*tmp;
	char	**str;
	size_t	iter;

	iter = 0;
	str = sort_env(env_to_array(master->env_list));
	while (str[iter])
	{
		tmp = ft_strchr(str[iter], '=');
		if (write(1, "declare -x ", 11) < 0)
			return (print_error(ft_strjoin("ba.sh: ", strerror(errno)), 1));
		if ((tmp && write(1, str[iter], tmp - str[iter] + 1) < 0)
			|| (!tmp && write(1, str[iter], ft_strlen(str[iter])) < 0))
			return (print_error(ft_strjoin("ba.sh: ", strerror(errno)), 1));
		if (write(1, "\"", 1) < 0)
			return (print_error(ft_strjoin("ba.sh: ", strerror(errno)), 1));
		if ((tmp && write(1, tmp + 1, ft_strlen(tmp)) < 0)
			|| (!tmp && write(1, str[iter], ft_strlen(str[iter])) < 0))
			return (print_error(ft_strjoin("ba.sh: ", strerror(errno)), 1));
		if (write(1, "\"", 1) < 0)
			return (print_error(ft_strjoin("ba.sh: ", strerror(errno)), 1));
		if (write(1, "\n", 1) < 0)
			return (print_error(ft_strjoin("ba.sh: ", strerror(errno)), 1));
		iter++;
	}
	return (0);
}
