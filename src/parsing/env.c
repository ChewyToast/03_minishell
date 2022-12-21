/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmoll-pe <bmoll-pe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/15 13:45:04 by aitoraudica       #+#    #+#             */
/*   Updated: 2022/12/21 17:04:14 by bmoll-pe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "structs.h"
#include "minishell.h"
#include "bmlib.h"

static int	env_new_value(t_env **list, char *name, char *value);
static t_env	*env_search(t_env *list, char *name);

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

/*---------------------------- STATIC SECTION -------------------------------*/

static t_env	*env_search(t_env *list, char *name)
{
	while (list)
	{
		if (!strcmp (list->name, name))
			return (list);
		list = list->next;
	}
	return (NULL);
}

static int	env_new_value(t_env **list, char *name, char *value)
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
