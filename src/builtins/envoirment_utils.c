/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envoirment_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: test <test@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/05 12:53:22 by test              #+#    #+#             */
/*   Updated: 2023/03/05 12:57:55 by test             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "defines.h"
#include "env.h"

void	prepare_next_export(t_node *node)
{
	size_t	iter;

	iter = 1;
	while (node->tokens[iter])
	{
		if (iter == 1)
			free(node->tokens[iter]);
		node->tokens[iter] = node->tokens[iter + 1];
		if (node->tokens[iter])
			iter++;
	}
}

int8_t	set_new_values(t_master *master, char *name, char *value)
{
	int8_t	rtrn;

	rtrn = 0;
	if (env_search(master->env_list, name))
	{
		if ((value && *value == '=' && env_change_value(master->env_list, name, value + 1))
			|| (value && *value == '+' && env_change_value(master->env_list, name, ft_strjoin(env_get_value(master->env_list, name), value + 2)))
			|| (!value && env_change_value(master->env_list, name, NULL)))
			rtrn = 1;
	}
	else if ((value && *value == '=' && env_new_value(&(master->env_list), name, value + 1))
			|| (value && *value == '+' && env_new_value(&(master->env_list), name, value + 2))
			|| (!value && env_new_value(&(master->env_list), name, NULL)))
		rtrn = 1;
	if (name)
		free(name);
	if (value)
		free(value);
	return (rtrn);
}

char	**sort_env(char **env)
{
	size_t	i;
	size_t	j;
	char	*tmp;

	i = 0;
	while (env[i + 1])
	{
		j = i + 1;
		while (env[j])
		{
			if (ft_strncmp(env[i], env[j], 0xffffff) > 0)
			{
				tmp = env[i];
				env[i] = env[j];
				env[j] = tmp;
			}
			j++;
		}
		i++;
	}
	return (env);
}