/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buildin_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: test <test@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 21:41:37 by bmoll-pe          #+#    #+#             */
/*   Updated: 2023/02/08 18:00:17 by test             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "structs.h"
#include "minishell.h"
#include "bmlib.h"
#include <limits.h>
/*
HAY QUE VER CON LOS ERRORES, HACEMOS EXIT? RETURN?
*/

bool	isalphanum(char *str);

char	*get_current_pwd(void)
{
	char	*pwd;
	char	*tmp;

	pwd = ft_calloc(PATH_MAX + 1, 1);
	if (!getcwd(pwd, PATH_MAX))
		return (print_error(ft_strdup("ba.sh: Error trying to allocate memory"), 1));
	tmp = ft_substr(pwd, 0, 0xffffffff);
	free (pwd);
	pwd = NULL;
	if (!tmp)
		return (print_error(ft_strdup("ba.sh: Error trying to allocate memory"), 1));
	return (tmp);
}

int	get_export_values(t_node *node, char **name, char **value)// no estoy muy orgulloso de esto... nose como vamos a devolver los errores
{
	char	*tmp;

	tmp = ft_strchr(node->tokens[1], '=');
	if (tmp && tmp > node->tokens[1])
	{
		*name = ft_substr(node->tokens[1], 0, tmp - node->tokens[1]);
		if (!(*name))
			return (print_error(ft_strdup("ba.sh: Error trying to allocate memory"), 1));
		*value = ft_substr(node->tokens[1], (tmp - node->tokens[1]), 0xffffffff);
		ft_printf("valuee: ->%s<-\n", *value);
		if (!(*value))
		{
			free(*name);
			return (print_error(ft_strdup("ba.sh: Error trying to allocate memory"), 1));
		}
	}
	else
	{
		*name = ft_substr(node->tokens[1], 0, 0xffffffff);
		if (!(*name))
			error("ba.sh: Error trying to allocate memory\n", 1);// ERROR!!!!
	}
	if (!ft_isalpha(**name) || !isalphanum(*name))
	{
		// write(2, "ba.sh: export: `", 16);
		// write(2, *name, ft_strlen(*name));
		// write(2, "\': not a valid identifier\n", 27);
		// free(*name);
		if (*value)
			free(*value);
		return (print_error(ft_strjoin("ba.sh: export: `", ft_strjoin_free(*name, ft_strdup("\': not a valid identifier"))), 1));
	}
	return (0);
}

bool	isalphanum(char *str)
{
	while (*str && ft_isalnum(*str))
		str++;
	if (*str)
		return (false);
	return (true);
}