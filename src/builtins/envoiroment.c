/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envoiroment.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: test <test@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 12:02:19 by test              #+#    #+#             */
/*   Updated: 2023/03/01 20:28:56 by test             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "defines.h"
#include "env.h"
#include "utils.h"
#include "builtin_utils.h"

static int8_t	set_new_values(t_master *master, char *name, char *value);
static void		prepare_next_export(t_node *node);
static int		print_export(t_master *master);
static char		**sort_env(char **env);

int	exec_export(t_master *master, t_node *node)
{
	char	*name;
	char	*value;
	int8_t	rtrn;

	rtrn = 0;
	if (node->tokens[0] && !node->tokens[1])
		return (print_export(master));
	while (node->tokens[1])
	{
		name = NULL;
		value = NULL;
		if (get_export_values(node, &name, &value))
			return (1);
		ft_printf("NEW values: %s=%s\n", name, value);
		rtrn = set_new_values(master, name, value);
		prepare_next_export(node);
	}
	if (rtrn)
		return (print_error(ft_strdup("ba.sh: Error trying to allocate memory"), 1));
	return (rtrn);
}

int	exec_unset(t_master *master, t_node *node)
{
	char	**tokens;

	tokens = node->tokens;
	tokens += 1;
	while (*(tokens))
		env_unset_node(master, *(tokens++));
	return (0);
}

static void	prepare_next_export(t_node *node)
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

static int8_t	set_new_values(t_master *master, char *name, char *value)
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

static int	print_export(t_master *master)
{
	char	*tmp;
	char	**str;
	size_t	iter;

	iter = 0;
	str = sort_env(env_to_array(master->env_list));
	while (str[iter])
	{
		tmp = ft_strchr(str[iter], '=');
		if (write(1, "declare -x ", 11) < 0)
			return (print_error(ft_strjoin("ba.sh: ", strerror(errno)), 1));
		if ((tmp && write(1, str[iter], tmp - str[iter] + 1) < 0)
			|| (!tmp && write(1, str[iter], ft_strlen(str[iter])) < 0))
			return (print_error(ft_strjoin("ba.sh: ", strerror(errno)), 1));
		if (write(1, "\"", 1) < 0)
			return (print_error(ft_strjoin("ba.sh: ", strerror(errno)), 1));
		if ((tmp && write(1, tmp + 1, ft_strlen(tmp)) < 0)
			|| (!tmp && write(1, str[iter], ft_strlen(str[iter])) < 0))
			return (print_error(ft_strjoin("ba.sh: ", strerror(errno)), 1));
		if (write(1, "\"", 1) < 0)
			return (print_error(ft_strjoin("ba.sh: ", strerror(errno)), 1));
		if (write(1, "\n", 1) < 0)
			return (print_error(ft_strjoin("ba.sh: ", strerror(errno)), 1));
		iter++;
	}
	return (0);
}

static char	**sort_env(char **env)
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
