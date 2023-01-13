/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmoll-pe <bmoll-pe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/15 13:45:04 by aitoraudica       #+#    #+#             */
/*   Updated: 2023/01/13 17:01:44 by bmoll-pe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "structs.h"
#include "minishell.h"
#include "bmlib.h"
/*---------------------------- PUBLIC SECTION --------------------------------*/

/*----------------------------------------------------------------------------
| ----/ Bfrief:	Print al the linked list of env
| ----/ Params:	Pointer to first node of the list
| ----/ Return:	Void
*----------------------------------------------------------------------------*/

void	print_env(t_env *env_list)
{
	fprintf(stderr, "---------> ENV:\n\n");
	while (env_list)
	{
		fprintf(stderr, "- %s=%s\n", env_list->name, env_list->value);
		env_list = env_list->next;
	}
	fprintf(stderr, "\n<---------\n\n");
}

/*----------------------------------------------------------------------------
| ----/ Bfrief:	Create linked list with all the envs values
| ----/ Params:	Double pointer to env table
| ----/ Return:	Pointer to first node of the list
*----------------------------------------------------------------------------*/

t_env	*env_parser(char **env)
{
	t_env	*env_list;
	char	**values;
	int		i;

	env_list = NULL;
	i = -1;
	while (env[++i])
	{
		values = ft_split(env[i], '=');
		env_new_value(&env_list, values[0], values[1]);
		free (values[0]);
		free (values[1]);
		free (values);
	}
	return (env_list);
}

/*-------------------------------------------------
| ----/ Bfrief:	Split the Path in substrings
| ----/ Params:	Pointer to first node of the list
| ----/ Return:	Double pointer with all the paths
*--------------------------------------------------*/
char	**env_get_path(t_env *list)
{
	t_env	*env;
	char	**path;

	env = env_search(list, "PATH");
	path = ft_split(env->value, ':');
	return (path);
}

char **env_to_array(t_env *list)
{
	char	**env_to_array;
	int 	num_envs;
	char	*env;
	char	*temp;

	env_to_array = NULL;
	num_envs = 0;
	while (list)
	{
		env_to_array = ft_realloc(env_to_array, (num_envs + 2) * sizeof (char*));
		if (env_to_array == NULL)
			return (NULL);
		temp = ft_strjoin(list->name, "=");
		env = ft_strjoin(temp, list->value);
		free(temp);
		env_to_array[num_envs++] = env;
		list = list->next;
	}
	env_to_array[num_envs] = NULL;
	return (env_to_array);
}

int	env_new_value(t_env **list, char *name, char *value)
{
	t_env	*elem;

	elem = malloc(sizeof(t_env));
	if (!elem)
		return (1);
	elem->name = ft_strdup(name);
	elem->value = ft_strdup(value);
	elem->next = NULL;
	elem->prev = NULL;
	if (*list)
	{
		(*list)->prev = elem;
		elem->next = *list;
	}
	*list = elem;
	return (0);
}
