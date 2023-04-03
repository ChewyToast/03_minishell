/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envoirment_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmoll-pe <bmoll-pe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/05 12:53:22 by test              #+#    #+#             */
/*   Updated: 2023/04/03 17:27:08 by bmoll-pe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "defines.h"
#include "env.h"

static bool	value_condition(t_master *master, char *name, char *value);

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

	rtrn = value_condition(master, name, value);
	if (name)
		free(name);
	if (value)
		free(value);
	return (rtrn);
}

static bool	value_condition(t_master *master, char *name, char *value)
{
	if (env_search(master->env_list, name))
	{
		if ((value && *value == '='
				&& env_change_value(master->env_list, name, value + 1))
			|| (value && *value == '+'
				&& env_change_value(master->env_list,
					name, ft_strjoin(env_get_value(master->env_list,
							name), value + 2)))
			|| (!value && env_change_value(master->env_list,
					name, NULL)))
			return (1);
	}
	else if ((value && *value == '='
			&& env_new_value(&(master->env_list), name, value + 1))
		|| (value && *value == '+'
			&& env_new_value(&(master->env_list), name, value + 2))
		|| (!value && env_new_value(&(master->env_list), name, NULL)))
		return (1);
	return (0);
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

void	free_envc(char	**envc)
{
	int	i;

	if (!envc)
		return ;
	i = 0;
	while (envc[i])
	{
		free(envc[i]);
		i++;
	}
	free (envc);
}
