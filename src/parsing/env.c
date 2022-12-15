/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aitoraudicana <aitoraudicana@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/15 13:45:04 by aitoraudica       #+#    #+#             */
/*   Updated: 2022/12/15 14:31:30 by aitoraudica      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "structs.h"
#include "minishell.h"
#include "bmlib.h"

t_env	*add_env_node(t_env *list, t_env *new);
t_env	*new_env_node(char *env_line);

t_env	*env_parser(char **env)
{
	t_env	*env_list;
	int		i;

	i = -1;
	while (env[++i] && env_list)
		env_list = add_env_node(env_list, new_env_node(env[i]));
	return (env_list);
}

t_env	*add_env_node(t_env *list, t_env *new)
{
	if (list && new)
		new->next = list;
	else
		return (NULL);
	return (new);
}

t_env	*new_env_node(char *env_line)
{
	char	**values;
	t_env	*elem;

	elem = malloc(sizeof(t_env));
	if (!elem)
		return (NULL);
	values = ft_split(env_line, '=');
	if (!values)
		return (NULL);
	elem->name = values[0];
	elem->value = values[1];
	return (elem);
}

void free_env_list(t_env *list)
{
	t_env	*temp;

	while (list)
	{
		temp = list->next;
		free(list->name);
		free(list->value);
		free(list);
		list = temp;
	}
}


