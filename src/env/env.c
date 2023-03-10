/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ailopez- <ailopez-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: Invalid date        by                   #+#    #+#             */
/*   Updated: 2023/03/10 23:28:39 by ailopez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */



#include "defines.h"
#include "env.h"
#include "utils.h"

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
| ----/ Bfrief:	Convert the list of envs to double string
| ----/ Params:	Pointer to first node of the list
| ----/ Return:	Double pointer with all the envs
*--------------------------------------------------*/

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
		env_to_array = ft_realloc(env_to_array, (num_envs + 2) * sizeof(char *));
		if (env_to_array == NULL)
			return (NULL);
		temp = ft_strjoin(list->name, "=");
		if (list->value)
			env = ft_strjoin(temp, list->value);
		else
			env = ft_strdup(temp);
		free(temp);
		env_to_array[num_envs++] = env;
		list = list->next;
	}
	env_to_array[num_envs] = NULL;
	return (env_to_array);
}

/*----------------------------------------------------------------------------
| ----/ Bfrief:	Get the value of one of the variables of enviroment
| ----/ Params:	Pointer to first node of the list
				Name of the variable
| ----/ Return:	String with the value of the variable, Null if does not exist
*----------------------------------------------------------------------------*/

char	*env_get_value(t_env *list, char *name)
{
	t_env	*env;

	if (!list || !name)
		return (NULL);
	env = env_search(list, name);
	if (env == NULL || env->value == NULL)
		return (NULL);
	return (ft_strdup(env->value));
}

/*----------------------------------------------------------------------------
| ----/ Bfrief:	Set the value of one of the variables of enviroment
| ----/ Params:	Pointer to first node of the list
				Name of the variable
				Value of the variable
| ----/ Return:	Void
*----------------------------------------------------------------------------*/

void	env_set_value(t_env **list, char *name, char *value)
{
	t_env	*env;

	if (!list || !name || !value || !*list)
		return ;
	env = env_search(*list, name);
	if (env == NULL)
		env_new_value(list, name, value);
	else
	{
		free (env->value);
		env->value = ft_strdup(value);
	}
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