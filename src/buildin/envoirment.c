/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envoirment.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: test <test@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 12:02:19 by test              #+#    #+#             */
/*   Updated: 2023/02/07 13:53:51 by test             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "structs.h"
#include "minishell.h"
#include "bmlib.h"

static int	print_export(t_master *master);

int	exec_export(t_master *master, t_node *node)
{
	char	*name;
	char	*value;
	int8_t	rtrn;
	size_t	util;

	rtrn = 0;
	if (node->tokens[0] && !node->tokens[1])
		return (print_export(master));
	while (node->tokens[1])
	{
		name = NULL;
		value = NULL;
		if (get_export_values(node, &name, &value))
			return (1);
		if (env_search(master->env_list, name))
		{
			if ((value && env_change_value(master->env_list, name, value + 1))
				|| (!value && env_change_value(master->env_list, name, NULL)))
				rtrn = 1;// ERROR !!
		}
		else if ((value && env_new_value(&(master->env_list), name, value + 1))
				|| (!value && env_new_value(&(master->env_list), name, NULL)))
			rtrn = 1;// ERROR !!
		if (name)
			free(name);
		if (value)
			free(value);
		util = 1;
		while (node->tokens[util])
		{
			if (util == 1)
				free(node->tokens[util]);
			node->tokens[util] = node->tokens[util + 1];
			if (node->tokens[util])
				util++;
		}
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

static int	print_export(t_master *master)
{
	t_env	*tmp;

	tmp = master->env_list;
	while (tmp)
	{
		write(1, "declare -x ", 11);
		if (tmp->name)
			write(1, tmp->name, ft_strlen(tmp->name));
		if (tmp->value)
		{
			write(1, "=\"", 2);
			write(1, tmp->value, ft_strlen(tmp->value));
			write(1, "\"", 1);
		}
		write(1, "\n", 1);
		tmp = tmp->next;
	}
	return (0);
}
