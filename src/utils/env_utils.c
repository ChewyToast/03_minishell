/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aitoraudicana <aitoraudicana@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/21 19:34:00 by bmoll-pe          #+#    #+#             */
/*   Updated: 2023/02/09 12:53:51 by aitoraudica      ###   ########.fr       */
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

	if (!list || !name)
		return (NULL);
	env = env_search(list, name);
	if (env == NULL)
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

/*----------------------------------------------------------------------------
| ----/ Bfrief:	Unset the value of one of the variables of enviroment
| ----/ Params:	Pointer to first node of the list
				Name of the variable
				Value of the variable
| ----/ Return:	Void
*----------------------------------------------------------------------------*/

void	env_unset_node(t_master *master, char *name)
{
	t_env	*env;

	if (!master || !name)
		return;
	env = env_search(master->env_list, name);
	if (env == NULL)
		return ;
	else
	{
		if (env->next && env->prev)
			env->prev->next = env->next;
		else if (env->next && !env->prev)
			master->env_list = env->next;
		else
			env->prev->next = NULL;
	}
	if (env->name)
		free (env->name);
	if (env->value && *env->value)
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

_Bool	env_change_value(t_env	*list, char *name, char *value)
{
	t_env	*node;

	node = env_search(list, name);
	if (!node)
		return (EXIT_SUCCESS);
	free(node->value);
	node->value = ft_substr(value, 0, 0xffffffff);
	if (!node->value)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}