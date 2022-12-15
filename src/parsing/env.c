/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmoll-pe <bmoll-pe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/15 13:45:04 by aitoraudica       #+#    #+#             */
/*   Updated: 2022/12/15 16:53:21 by bmoll-pe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "structs.h"
#include "minishell.h"
#include "bmlib.h"

t_env	*env_add_node(t_env *list, t_env *new);
t_env	*env_new_node(char *env_line);

void	print_env(t_env *env_list)
{
	fprintf(stderr, "---------> ENV:\n\n");
	while(env_list)
	{
		fprintf(stderr, "- %s=%s\n", env_list->name, env_list->value);
		env_list = env_list->next;
	}
	fprintf(stderr, "\n<---------\n\n");
}

t_env	*env_parser(char **env)
{
	t_env	*env_list;
	int		i;

	i = 0;
	env_list = env_new_node(env[i]);
	while (env[++i] && env_list)
		env_list = env_add_node(env_list, env_new_node(env[i]));
	return (env_list);
}

t_env	*env_search(t_env *list, char *name)
{
	while (list)
	{
		if (strcmp (list->name, name))
			return (list);
		list = list->next;
	}
	return (NULL);
}

t_env	*env_add_node(t_env *list, t_env *new)
{
	if (list && new)
		new->next = list;
	else
		return (NULL);
	return (new);
}

t_env	*env_new_node(char *env_line)
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
	elem->next = NULL;
	return (elem);
}

t_env	*env_new_value(t_env *list, char *name, char *value)
{
	t_env	*elem;

	elem = malloc(sizeof(t_env));
	if (!elem)
		return (NULL);
	elem->name = ft_strdup(name);
	elem->value = ft_strdup(value);
	elem->next = NULL;
	while (list->next)
		list = list->next;
	list->next = elem;
	return (elem);
}

void	env_free_list(t_env *list)
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
