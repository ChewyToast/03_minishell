/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmoll-pe <bmoll-pe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 21:41:37 by bmoll-pe          #+#    #+#             */
/*   Updated: 2023/03/09 20:22:50 by bmoll-pe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "defines.h"
#include "builtin_utils.h"
#include "utils.h"

/*
HAY QUE VER CON LOS ERRORES, HACEMOS EXIT? RETURN?
*/

char	*get_current_pwd(void)
{
	char	*pwd;
	char	*tmp;

	pwd = ft_calloc(PATH_MAX + 1, 1);
	if (!getcwd(pwd, PATH_MAX))
	{
		print_error(NULL, 0, 1);
		return (NULL);
	}
	tmp = ft_substr(pwd, 0, 0xffffffff);
	free (pwd);
	pwd = NULL;
	if (!tmp)
	{
		print_error(NULL, 0, 1);
		return (NULL);
	}
	return (tmp);
}

int	get_export_values(t_node *node, char **name, char **value)// no estoy muy orgulloso de esto... nose como vamos a devolver los errores
{
	char	*tmp;
	char	*symbl;

	tmp = ft_strchr(node->tokens[1], '=');
	symbl = ft_strchr(node->tokens[1], '+');
	if (tmp && tmp > node->tokens[1])
	{
		if (symbl && symbl == tmp - 1 && symbl > node->tokens[1])
			tmp = symbl;
		*name = ft_substr(node->tokens[1], 0, tmp - node->tokens[1]);
		if (!(*name))
			return (print_error(NULL, 0, 1));
		*value = ft_substr(node->tokens[1], (tmp - node->tokens[1]), 0xffffffff);
		if (!(*value))
		{
			free(*name);
			return (print_error(NULL, 0, 1));
		}
	}
	else
	{
		*name = ft_substr(node->tokens[1], 0, 0xffffffff);
		if (!(*name))
			exit_program(NULL, 0, 1);
	}
	if (!is_valid_name(*name))
	{
		if (*value)
			free(*value);
		free(*name);
		return (print_error(ft_strjoin("export: `", ft_strjoin_free(ft_strdup(node->tokens[1]), ft_strdup("\': not a valid identifier"))), 1, 1));
	}
	return (0);
}

bool	is_valid_name(char *str)
{
	if (!str || !(*str) || (!ft_isalpha(*str) && *str != '_'))
		return (false);
	while (*str && (ft_isalnum(*str) || *str == '_'))
		str++;
	if (*str)
		return (false);
	return (true);
}