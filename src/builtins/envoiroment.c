/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envoiroment.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmoll-pe <bmoll-pe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 12:02:19 by test              #+#    #+#             */
/*   Updated: 2023/04/05 17:57:33 by bmoll-pe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "defines.h"
#include "env.h"
#include "utils.h"
#include "builtin_utils.h"
#include "envoirment_utils.h"

static int	print_export_util(char *tmp, char **str, size_t iter);

int	exec_env(t_master *master, t_node *node)
{
	size_t	iter;
	char	**print;

	(void)node;
	iter = 0;
	print = env_to_array(master->env_list);
	if (!print)
		exit_program(NULL, 0, 1);
	while (print[iter])
	{
		if (ft_strchr(print[iter], '='))
		{
			if (write(1, print[iter], ft_strlen(print[iter])) < 1)
				exit_program(NULL, 0, 1);
			if (write(1, "\n", 1) < 1)
				exit_program(NULL, 0, 1);
		}
		iter++;
	}
	free_envc(print);
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
			rtrn = 1;
		set_new_values(master, name, value);
		prepare_next_export(node);
	}
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
		if (!tmp)
		{
			tmp = ft_strjoin("declare -x ", str[iter]);
			if (write(1, tmp, ft_strlen(tmp)) < 1)
				return (print_error(NULL, 0, free_split(str)));
			free(tmp);
		}
		else if (print_export_util(tmp, str, iter))
			return (free_split(str));
		if (write(1, "\n", 1) < 0)
			return (print_error(NULL, 0, free_split(str)));
		iter++;
	}
	free_split(str);
	return (0);
}

static int	print_export_util(char *tmp, char **str, size_t iter)
{
	bool	err;

	err = 0;
	if (write(1, "declare -x ", 11) < 0)
		err = 1;
	if ((tmp && write(1, str[iter], tmp - str[iter] + 1) < 0)
		|| (!tmp && write(1, str[iter], ft_strlen(str[iter])) < 0))
		err = 1;
	if (write(1, "\"", 1) < 0)
		err = 1;
	if ((tmp && write(1, tmp + 1, ft_strlen(tmp) - 1) < 0)
		|| (!tmp && write(1, str[iter], ft_strlen(str[iter])) < 0))
		err = 1;
	if (write(1, "\"", 1) < 0)
		err = 1;
	if (err)
	{
		free(tmp);
		g_global.num_return_error = 1;
		return (print_error(NULL, 0, 1));
	}
	return (0);
}
