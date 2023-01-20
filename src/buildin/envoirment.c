/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envoirment.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: test <test@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 12:02:19 by test              #+#    #+#             */
/*   Updated: 2023/01/20 13:57:56 by test             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "structs.h"
#include "minishell.h"
#include "bmlib.h"

static int	print_export(t_master *master);

int	exec_export(t_master *master, t_node *node)
{
	t_env	*tmp;
	char	*name;
	char	*value;
	int		rtrn;

	name = NULL;
	value = NULL;
	ft_printf("EXPORT!!!\n");
	rtrn = 0;
	if (node->tokens[0] && !node->tokens[1])
		return (print_export(master));// falta imprimiro como lo hace el mierder del bash
	if (get_export_values(node, &name, &value))
		return (1);
	tmp = env_search(master->env_list, name);
	if (tmp)
	{
		if (env_change_value(master->env_list, name, value))
			rtrn = 1;
	}
	else if (env_new_value(&(master->env_list), name, value))// AQUI ME DI CUENTA QUE... algunas funciones de env no estan los malloc protegidos
		rtrn = 1;
	if (name)
		free(name);
	if (value)
		free(value);
	return (rtrn);
}

int	exec_unset(t_master *master, t_node *node)
{
	ft_printf("UNSET!!!\n");
	env_unset_node(master->env_list, node->tokens[1]);
	return (0);
}

static int	print_export(t_master *master)
{
	print_env(master->env_list);
	return (0);
}