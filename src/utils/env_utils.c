/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmoll-pe <bmoll-pe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/21 19:34:00 by bmoll-pe          #+#    #+#             */
/*   Updated: 2023/01/17 16:45:13 by bmoll-pe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "structs.h"
#include "minishell.h"
#include "bmlib.h"

/*----------------------------------------------------------------------------
| ----/ Bfrief:	Free all the memory of env list
| ----/ Params:	Pointer to first node of the list
| ----/ Return:	Void
*----------------------------------------------------------------------------*/

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

/*----------------------------------------------------------------------------
| ----/ Bfrief:	Get the value of one of the variables of enviroment
| ----/ Params:	Pointer to first node of the list
				Name of the variable
| ----/ Return:	String with the value of the variable, Null if does not exist
*----------------------------------------------------------------------------*/

char	*env_get_value(t_env *list, char *name)
{
	t_env	*env;

	env = env_search(list, name);
	return (env->value);
}

/*----------------------------------------------------------------------------
| ----/ Bfrief:	Set the value of one of the variables of enviroment
| ----/ Params:	Pointer to first node of the list
				Name of the variable
				Value of the variable
| ----/ Return:	Void
*----------------------------------------------------------------------------*/

void	env_set_value(t_env *list, char *name, char *value)
{
	t_env	*env;

	env = env_search(list, name);
	if (env == NULL)
		env_new_value(&list, name, value);
	else
	{
		free (env->value);
		env->value = ft_strdup(value);
	}
}

/*----------------------------------------------------------------------------
| ----/ Bfrief:	Unset the value of one of the variables of enviroment
| ----/ Params:	Pointer to first node of the list
				Name of the variable
				Value of the variable
| ----/ Return:	Void
*----------------------------------------------------------------------------*/

void	env_unset_value(t_env *list, char *name)
{
	t_env	*env;

	env = env_search(list, name);
	if (env == NULL)
		return ;
	else
	{
		if (env->next)
			env->prev->next = env->next;
		else
			env->prev->name = NULL;
	}
	free (env->value);
	free (env->value);
	free (env);
}

t_env	*env_search(t_env *list, char *name)
{
	if (!list || !name || !(*name))
		return (NULL);
	while (list)
	{
		if (!ft_strncmp(list->name, name, 0xffffffff))
			return (list);
		list = list->next;
	}
	return (NULL);
}

char	*env_value_search(t_env *list, char *name)
{
	if (!list || !name || !(*name))
		return (NULL);
	while (list)
	{
		if (!ft_strncmp(list->name, name, 0xffffffff))
			return (list->value);
		list = list->next;
	}
	return (NULL);
}